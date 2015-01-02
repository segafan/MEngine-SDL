//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Rect.h"
#include "Color.h"
#include "Logger.h"
#include "System.h"

class Display
{
public:
	Display();
	~Display();

	bool Create2D(std::string title, int w, int h, int flags, bool TargetTexture, bool VSYNC, float FPS);
	bool Create3D(std::string title, int w, int h, int flags);

	Rect& GetSize();
	int& GetW();
	int& GetH();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	void Clear();
	void Present();

	void SetRenderColor(Color color);
	void SetRenderColor(SDL_Color color);
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b);
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a);

	void PushRenderColor();
	void PopRenderColor();

	Color& GetRenderColor();

	bool Is3D();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_GLContext glContext;

	bool is3D;

	int ScreenWidth;
	int ScreenHeight;

	std::vector<Color> renderColorStack;

	Color color;
	Rect ScreenPos;
};

//TODO: Add screenshot creation if using OpenGL for 3D rendering
inline bool CreateScreenshot(Display* display)
{
	SDL_Surface* saveSurface = NULL;
	SDL_Surface* infoSurface = NULL;

	infoSurface = SDL_GetWindowSurface(display->GetWindow());

	if (infoSurface == NULL)
	{
		LOG_ERROR("Failed to create info surface from window in CreateScreenshot()! Error: " << SDL_GetError());
	}
	else
	{
		unsigned char * pixels = new (std::nothrow) unsigned char[infoSurface->w * infoSurface->h * infoSurface->format->BytesPerPixel];
		if (pixels == 0)
		{
			LOG_ERROR("Unable to allocate memory for screenshot pixel data buffer!");
			return false;
		}
		else
		{
			if (SDL_RenderReadPixels(display->GetRenderer(), &infoSurface->clip_rect, infoSurface->format->format, pixels, infoSurface->w * infoSurface->format->BytesPerPixel) != 0)
			{
				LOG_ERROR("Failed to read pixel data from SDL_Renderer object. Error: " << SDL_GetError());
				pixels = NULL;
				return false;
			}
			else
			{
				saveSurface = SDL_CreateRGBSurfaceFrom(pixels, infoSurface->w, infoSurface->h, infoSurface->format->BitsPerPixel, infoSurface->w * infoSurface->format->BytesPerPixel, infoSurface->format->Rmask, infoSurface->format->Gmask, infoSurface->format->Bmask, infoSurface->format->Amask);

				if (saveSurface == NULL)
				{
					LOG_ERROR("Couldn't create SDL_Surface from renderer pixel data. Error: " << SDL_GetError());
					return false;
				}

				std::string screenshotName = GetScreenshotName();

				if (IMG_SavePNG(saveSurface, screenshotName.c_str()) == 0)
				{
					LOG("Created Screenshot: " << screenshotName << "!");
				}
				else
					LOG_ERROR("Screenshot couldn't be saved! Error: " << SDL_GetError());

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