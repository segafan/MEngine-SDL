//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_syswm.h>

#include "Config.h"
#include "Util.h"
#include "Logger.h"
#include "RenderSupport.h"
#include "Random.h"

static int Init()
{
	//TODO: Log this
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw "Error SDL_Init!";
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
			throw "Error IMG_Init!";
		if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
			throw "Error Mix_Init!";
		if (Mix_OpenAudio(22050 * 2, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
			throw "Error Mix_OpenAudio!";
		if (TTF_Init() != 0)
			throw "Error TTF_Init()!";
		if (SDLNet_Init() != 0)
			throw "Error SDLNet_Init()!";
		
		if (!Random::IsSafe())
			std::cout << "Random Number Generation is using 32 bit time values which may cause problems after 2036!" << std::endl;

		Random::Init();
	}
	catch (char* error)
	{
		std::cout << error << " Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

static void Quit()
{
	SDL_StopTextInput();

	SDL_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDLNet_Quit();
}

static void LogSDLInfo()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	LOG_PURE("Compiled SDL: " << (int)compiled.major << "." << (int)compiled.minor << "." << (int)compiled.patch);
	LOG_PURE("Linked SDL: " << (int)linked.major << "." << (int)linked.minor << "." << (int)linked.patch);

	Logger::Instance()->NewLine();
}

static void LogSystemInfo()
{
	LOG_PURE("Logical CPU Cores: " << SDL_GetCPUCount());
	LOG_PURE("RAM: " << SDL_GetSystemRAM() << " MB");
	Logger::Instance()->NewLine();
}

static void LogSubSystemInfo(SDL_Window *window)
{
	SDL_SysWMinfo info;

	if (SDL_GetWindowWMInfo(window, &info))
	{
		const char *subsystem = "Unknown System";
		switch (info.subsystem)
		{
			case SDL_SYSWM_UNKNOWN:   break;
			case SDL_SYSWM_WINDOWS:   subsystem = "Microsoft Windows";      break;
			case SDL_SYSWM_X11:       subsystem = "X Window System";        break;
			case SDL_SYSWM_DIRECTFB:  subsystem = "DirectFB";               break;
			case SDL_SYSWM_COCOA:     subsystem = "Apple OS X";             break;
			case SDL_SYSWM_UIKIT:     subsystem = "UIKit";                  break;
			case SDL_SYSWM_WAYLAND:	  subsystem = "Wayland";				break;
			case SDL_SYSWM_MIR:		  subsystem = "Mir";					break;
			case SDL_SYSWM_WINRT:	  subsystem = "Win RT";					break;
		}
		LOG_PURE("Subsystem: " << subsystem);
	}
	else
		LOG_PURE("Couldn't get used Subsystem");

	Logger::Instance()->NewLine();
}

static void LogOSInfo()
{
#if defined(OS_WINDOWS_32)
	LOG_PURE("Windows 32-bit");
#elif defined(OS_WINDOWS_64)
	LOG_PURE("Windows 64-bit");
#elif defined(OS_UNIX)
	LOG_PURE("Unix");
#elif defined(OS_MAC)
	LOG_PURE("Mac OSX");
#elif defined(OS_LINUX)
	LOG_PURE("Linux");
#elif defined(OS_POSIX)
	LOG_PURE("Posix");
#elif defined(OS_FREEBSD)
	LOG_PURE("FreeBSD");
#else
	LOG_PURE("Other OS");
#endif
}

inline bool IsVSyncGoodToUse(SDL_Window* window, float FPS)
{
	bool vsync = false;

	//Get window refresh rate
	SDL_DisplayMode mode;
	SDL_GetWindowDisplayMode(window, &mode);

	//Log window refresh rate
	if (mode.refresh_rate == 0)
	{
		LOG_PURE("Window refresh rate: " << "Unknown!");
	}
	else
		LOG_PURE("Window refresh rate: " << mode.refresh_rate);

	//Check if it's == FPS
	if (mode.refresh_rate >= (int)FPS)
	{
		LOG_PURE("Activating VSync if available, because it would help in FPS caping!");
		vsync = true;
	}
	else
	{
		//Try to get a good display mode
		mode.refresh_rate = (int)FPS;

		SDL_DisplayMode closestMode;
		SDL_GetClosestDisplayMode(0, &mode, &closestMode);

		if (closestMode.refresh_rate >= (int)FPS)
		{
			LOG_PURE("Found another Display Mode which has better refresh rate!");

			if (mode.w == closestMode.w && mode.h == closestMode.h)
			{
				if (mode.format == closestMode.format)
				{
					if (SDL_SetWindowDisplayMode(window, &closestMode) == 0)
					{
						LOG_PURE("The Display mode of the window has been set!");
						LOG_PURE("Window refresh rate is now: " << closestMode.refresh_rate);
						vsync = true;
					}
					else
					{
						LOG_PURE("Couldn't bind Display Mode to Window!");
						vsync = false;
					}
				}
				else
				{
					LOG_PURE("The Display Mode has other pixel format so it cannot be used!");
					vsync = false;
				}
			}
			else
			{
				LOG_PURE("The Display Mode has other resolution so it cannot be used!");
				vsync = false;
			}
		}
		else
		{
			LOG_PURE("Didn't find a display mode to use VSync!");
			vsync = false;
		}
	}

	Logger::Instance()->NewLine();

	return vsync;
}

inline SDL_Renderer* CreateAndLogRenderer(SDL_Window *window, bool targetTexture, bool vsync, float FPS)
{
	if (window == NULL)
	{
		LOG_ERROR("Couldn't create renderer because Window is NULL! Error: " << SDL_GetError());
		return NULL;
	}

	//TODO: After creating a new FPSTimer keep this or delete this
	//vsync = IsVSyncGoodToUse(window, logger, FPS);

	LogAllRenderInfo();

	Uint32 flags = GetRenderFlags(window, targetTexture, vsync);
	if (flags == 0)
	{
		LOG_ERROR("No Render Flags Available! Error: " << SDL_GetError());
		return NULL;
	}

	LogRenderFlags(flags);

	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, flags);

	if (renderer == NULL)
	{
		LOG_ERROR("Error creating Renderer! Error: " << SDL_GetError());
	}

	LogUsedRenderInfo(renderer);

	return renderer;
}

inline SDL_Window* CreateAndLogWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	LogSDLInfo();
	LogSystemInfo();
	LogOSInfo();

	SDL_Window *window = NULL;
	window = SDL_CreateWindow(title, x, y, w, h, flags);

	if (window == NULL)
	{
		LOG_ERROR("Error creating Window! Error: " << SDL_GetError());
		return NULL;
	}

	LogSubSystemInfo(window);

	return window;
}

inline SDL_Window* CreateAndLogWindow(const char* title, int w, int h, Uint32 flags)
{
	return CreateAndLogWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
}

inline std::string GetScreenshotName()
{
	std::string screenshotStart = "screenshots/screenshot-";
	std::string screenshotEnd = ".png";

	std::string date = GetDate();

	int screenshotNumber = 1;

	while (true)
	{
		std::string screenshotname = (screenshotStart + date + "-" + NumberToString(screenshotNumber) + screenshotEnd);

		if (!FileExits(screenshotname.c_str()))
			break;

		screenshotNumber++;
	}

	std::string fullscreenshotName = (screenshotStart + date + "-" + NumberToString(screenshotNumber) + screenshotEnd);

	return fullscreenshotName;
}

#endif