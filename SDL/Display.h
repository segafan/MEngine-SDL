//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef DISPLAY_H
#define DISPLAY_H

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Rect.h"
#include "Color.h"
#include "Logger.h"
#include "System.h"
#include "Camera.h"

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

	void SetCamera(Camera& camera);
	Camera& GetCamera();

	Color& GetRenderColor();

	bool Is3D();

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_GLContext glContext;

	Camera camera;

	bool is3D;

	int ScreenWidth;
	int ScreenHeight;

	std::vector<Color> renderColorStack;

	Color color;
	Rect ScreenPos;
};

inline bool CreateScreenshot2D(Display* display)
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

#define SDL_LOCKIFMUST(s) (SDL_MUSTLOCK(s) ? SDL_LockSurface(s) : 0)
#define SDL_UNLOCKIFMUST(s) { if(SDL_MUSTLOCK(s)) SDL_UnlockSurface(s); }

static int FlipSurfaceVertical(SDL_Surface *surface)
{
	Uint8 *t;
	register Uint8 *a, *b;
	Uint8 *last;
	register Uint16 pitch;

	if (SDL_LOCKIFMUST(surface) < 0)
		return -2;

	if (surface->h < 2) 
	{
		SDL_UNLOCKIFMUST(surface);
		return 0;
	}

	pitch = surface->pitch;
	t = (Uint8*)malloc(pitch);

	if (t == NULL) 
	{
		SDL_UNLOCKIFMUST(surface);
		return -2;
	}

	memcpy(t, surface->pixels, pitch);

	a = (Uint8*)surface->pixels;
	last = a + pitch * (surface->h - 1);
	b = last;

	while (a < b) 
	{
		memcpy(a, b, pitch);
		a += pitch;
		memcpy(b, a, pitch);
		b -= pitch;
	}

	memmove(b, b + pitch, last - b);

	memcpy(last, t, pitch);

	free(t);
	SDL_UNLOCKIFMUST(surface);

	return 0;
}

inline bool CreateScreenshot3D(Display* display)
{
	int x = 0;
	int y = 0;
	int w = display->GetW();
	int h = display->GetH();

	const int arraySize = w * h * 4;

	unsigned char * pixels = new unsigned char[arraySize]; // 4 bytes for RGBA
	glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	for (int i = 0; i < arraySize; i += 4)
	{
		unsigned char red = pixels[i + 2];
		unsigned char blue = pixels[i];

		pixels[i + 2] = blue;
		pixels[i] = red;
	}
	
	SDL_Surface * surf = SDL_CreateRGBSurfaceFrom(pixels, w, h, 8 * 4, w * 4, 0, 0, 0, 0);

	if (surf == NULL)
	{
		LOG_ERROR("Couldn't create surface from pixel data! Error: " << SDL_GetError());

		delete[] pixels;

		return false;
	}

	if (FlipSurfaceVertical(surf) != 0)
	{
		LOG_ERROR("Couldn't flip surface vertically! Error: " << SDL_GetError());

		SDL_FreeSurface(surf);
		surf = NULL;
		delete[] pixels;
		
		return false;
	}

	const std::string& screenshotName = GetScreenshotName();

	if (IMG_SavePNG(surf, screenshotName.c_str()) == 0)
	{
		LOG("Created Screenshot: " << screenshotName << "!");
	}
	else
	{
		LOG_ERROR("Screenshot couldn't be saved! Error: " << SDL_GetError());

		SDL_FreeSurface(surf);
		surf = NULL;
		delete[] pixels;

		return false;
	}

	SDL_FreeSurface(surf);
	surf = NULL;
	delete[] pixels;

	return true;
}

inline bool CreateScreenshot(Display* display)
{
	return (display->Is3D() ? CreateScreenshot3D(display) : CreateScreenshot2D(display));
}

#endif