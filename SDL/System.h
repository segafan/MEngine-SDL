#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL.h>
#include <SDL_syswm.h>

#include "Logger.h"
#include "RenderSupport.h"

inline SDL_Color MapRGB(int r, int g, int b)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;

	return color;
}

inline SDL_Rect SetValues(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

static int Init()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw "Error SDL_Init!";
		}
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		{
			throw "Error IMG_Init!";
		}
		if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
		{
			throw "Error Mix_Init!";
		}
		if (Mix_OpenAudio(22050 * 2, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			throw "Error Mix_OpenAudio!";
		}
		if (TTF_Init() != 0)
		{
			throw "Error TTF_Init()!";
		}
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
	//SDLNet_Quit();
}

static void LogSDLInfo(Logger *logger)
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	logger->LogLineWithoutDate("Compiled SDL: ", compiled.major, compiled.minor, compiled.patch);
	logger->LogLineWithoutDate("Linked SDL: ", linked.major, linked.minor, linked.patch);

	logger->NewLine();
}

static void LogSystemInfo(Logger *logger)
{
	logger->LogLineWithoutDate("Logical CPU Cores: ", NumberToString(SDL_GetCPUCount()).c_str());
	logger->LogLineWithoutDate("RAM: ", NumberToString(SDL_GetSystemRAM()).c_str(), " MB");
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
		}
		logger->LogLineWithoutDate("Subsystem: ", subsystem);
	}
	else
		logger->LogLineWithoutDate("Couldn't get used Subsystem");

	logger->NewLine();

}

static void LogOSInfo(Logger *logger)
{
#ifdef _WIN32
	logger->LogLineWithoutDate("Windows 32-bit");
#elif _WIN64
	logger->LogLineWithoutDate("Windows 64-bit");
#elif __unix || __unix__
	logger->LogLineWithoutDate("Unix");
#elif __APPLE__ || __MACH__
	logger->LogLineWithoutDate("Mac OSX");
#elif __linux__
	logger->LogLineWithoutDate("Linux");
#elif __FreeBSD__
	logger->LogLineWithoutDate("FreeBSD");
#else
	logger->LogLineWithoutDate("Other OS");
#endif
}

inline SDL_Renderer* CreateAndLogRenderer(SDL_Window *window, Logger *logger, bool targetTexture, bool vsync)
{
	LogAllRenderInfo(logger);

	Uint32 flags = GetRenderFlags(window, targetTexture, vsync);
	if (flags == NULL)
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