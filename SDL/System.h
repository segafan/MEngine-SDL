#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "Util.h"
#include "Logger.h"
#include "RenderSupport.h"

//Check if C++11 is supported
#if _MSC_VER >= 1600 || __cplusplus > 199711L
#define CPP11_SUPPORT
#elif _MSC_VER < 1600 || __cplusplus <= 199711L
#endif

//If no C++11 Support add some
#ifndef CPP11_SUPPORT
#define nullptr 0
#endif

//Define used Operating System
//TODO: Test this
#ifdef _WIN64
	#define OS_WINDOWS
	#define OS_WINDOWS_64
#elif _WIN32
	#define OS_WINDOWS
	#define OS_WINDOWS_32
#elif __APPLE__ || __MACH__
	#include "TargetConditionals.h"
	#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
		#define OS_IOS
	#elif TARGET_OS_MAC
		#define OS_MAC
	#else
		#define OS_APPLE_UNKNOWN
	#endif
#elif __ANDROID__ || __ANDROID_API__ || ANDROID || TARGET_OS_ANDROID
	#define OS_ANDROID
#elif __linux__ || __linux
	#define OS_LINUX
#elif __unix__ || __unix
	#define OS_UNIX
#elif __FreeBSD__
	#define OS_FREEBSD
#elif  __posix__ || __posix
	#define OS_POSIX
#elif CPP11_SUPPORT
	#define OS_OTHER_CPP11
#else
	#define OS_OTHER
#endif

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
	}
	catch (char* error)
	{
		std::cout << error << " Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	return 0;
}

static void Quit()
{
	SDL_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDLNet_Quit();
}

static void LogSDLInfo(Logger *logger)
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	logger->LogVersion("Compiled SDL: ", compiled.major, compiled.minor, compiled.patch);
	logger->LogVersion("Linked SDL: ", linked.major, linked.minor, linked.patch);

	logger->NewLine();
}

static void LogSystemInfo(Logger *logger)
{
	logger->LogLineWithoutTime("Logical CPU Cores: ", NumberToString(SDL_GetCPUCount()).c_str());
	logger->LogLineWithoutTime("RAM: ", NumberToString(SDL_GetSystemRAM()).c_str(), " MB");
	logger->NewLine();
}

static void LogSubSystemInfo(Logger *logger, SDL_Window *window)
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
		logger->LogLineWithoutTime("Subsystem: ", subsystem);
	}
	else
		logger->LogLineWithoutTime("Couldn't get used Subsystem");

	logger->NewLine();

}

static void LogOSInfo(Logger *logger)
{
#ifdef OS_WINDOWS_32
	logger->LogLineWithoutTime("Windows 32-bit");
#elif OS_WINDOWS_64
	logger->LogLineWithoutTime("Windows 64-bit");
#elif OS_UNIX
	logger->LogLineWithoutTime("Unix");
#elif OS_MAC
	logger->LogLineWithoutTime("Mac OSX");
#elif OS_LINUX
	logger->LogLineWithoutTime("Linux");
#elif OS_FREEBSD
	logger->LogLineWithoutTime("FreeBSD");
#else
	logger->LogLineWithoutTime("Other OS");
#endif
}

inline bool IsVSyncGoodToUse(SDL_Window* window, Logger* logger, float FPS)
{
	bool vsync = false;

	//Get window refresh rate
	SDL_DisplayMode mode;
	SDL_GetWindowDisplayMode(window, &mode);

	//Log window refresh rate
	if (mode.refresh_rate == 0)
		logger->LogLineWithoutTime("Window refresh rate: ", "Unknown!");
	else
		logger->LogLineWithoutTime("Window refresh rate: ", mode.refresh_rate);

	//Check if it's == FPS
	if (mode.refresh_rate >= (int)FPS)
	{
		logger->LogLineWithoutTime("Activating VSync if available, because it would help in FPS caping!");
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
			logger->LogLineWithoutTime("Found another Display Mode which has better refresh rate!");

			if (mode.w == closestMode.w && mode.h == closestMode.h)
			{
				if (mode.format == closestMode.format)
				{
					if (SDL_SetWindowDisplayMode(window, &closestMode) == 0)
					{
						logger->LogLineWithoutTime("The Display mode of the window has been set!");
						logger->LogLineWithoutTime("Window refresh rate is now: ", closestMode.refresh_rate);
						vsync = true;
					}
					else
					{
						logger->LogLineWithoutTime("Couldn't bind Display Mode to Window!");
						vsync = false;
					}
				}
				else
				{
					logger->LogLineWithoutTime("The Display Mode has other pixel format so it cannot be used!");
					vsync = false;
				}
			}
			else
			{
				logger->LogLineWithoutTime("The Display Mode has other resolution so it cannot be used!");
				vsync = false;
			}
		}
		else
		{
			logger->LogLineWithoutTime("Didn't find a display mode to use VSync!");
			vsync = false;
		}
	}

	logger->NewLine();

	return vsync;
}

inline SDL_Renderer* CreateAndLogRenderer(SDL_Window *window, Logger *logger, bool targetTexture, bool vsync, float FPS)
{
	if (window == NULL)
	{
		logger->LogLine("Couldn't create renderer because Window is NULL!");
		return NULL;
	}

	vsync = IsVSyncGoodToUse(window, logger, FPS);

	LogAllRenderInfo(logger);

	Uint32 flags = GetRenderFlags(window, targetTexture, vsync);
	if (flags == 0)
	{
		logger->LogLine("No Render Flags Available!");
		return NULL;
	}

	LogRenderFlags(flags, logger);

	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, flags);

	if (renderer == NULL)
	{
		logger->LogLine("Error creating Renderer! Error: ", SDL_GetError());
	}

	LogUsedRenderInfo(renderer, logger);

	return renderer;
}

inline SDL_Window* CreateAndLogWindow(const char* title, int x, int y, int w, int h, Uint32 flags, Logger* logger)
{
	LogSDLInfo(logger);
	LogSystemInfo(logger);
	LogOSInfo(logger);

	SDL_Window *window = NULL;
	window = SDL_CreateWindow(title, x, y, w, h, flags);

	if (window == NULL)
	{
		logger->LogLine("Error creating Window! Error: ", SDL_GetError());
		return NULL;
	}

	LogSubSystemInfo(logger, window);

	return window;
}

inline SDL_Window* CreateAndLogWindow(const char* title, int w, int h, Uint32 flags, Logger* logger)
{
	return CreateAndLogWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags, logger);
}

inline std::string GetScreenshotName()
{
	std::string screenshotStart = "screenshots/screenshot-";
	std::string screenshotEnd = ".png";

	std::string date = GetDate();

	static int screenshotNumber = 1;

	while (true)
	{
		std::string screenshotname = (screenshotStart + NumberToString(date) + "-" + NumberToString(screenshotNumber) + screenshotEnd);

		if (!FileExits(screenshotname.c_str()))
			break;

		screenshotNumber++;
	}

	std::string fullscreenshotName = (screenshotStart + NumberToString(date) + "-" + NumberToString(screenshotNumber) + screenshotEnd);

	return fullscreenshotName;
}

inline bool CreateScreenshot(SDL_Window* SDLWindow, SDL_Renderer* SDLRenderer)
{
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;

	infoSurface = SDL_GetWindowSurface(SDLWindow);

	if (infoSurface == NULL)
	{
		std::cerr << "Failed to create info surface from window in CreateScreenshot(string), SDL_GetError() - " << SDL_GetError() << "\n";
	}
	else
	{
		unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0)
		{
			std::cerr << "Unable to allocate memory for screenshot pixel data buffer!\n" << std::endl;
			return false;
		}
		else
		{
			if (SDL_RenderReadPixels(SDLRenderer, &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
			{
				std::cerr << "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - " << SDL_GetError() << "\n";
				pixels = NULL;
				return false;
			}
			else
			{
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

				if (saveSurface == NULL)
				{
					std::cerr << "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - " << SDL_GetError() << "\n";
					return false;
				}

				std::string screenshotName = GetScreenshotName();

				IMG_SavePNG(saveSurface, screenshotName.c_str());
				std::cout << "Created Screenshot: " << screenshotName << "!" << std::endl;

				SDL_FreeSurface(saveSurface);

				saveSurface = NULL;
			}
			delete[] pixels;
		}
		SDL_FreeSurface(infoSurface);
		infoSurface = NULL;
	}
	return true;
}

#endif