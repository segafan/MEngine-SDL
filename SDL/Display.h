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
	Display()
	{
		window = NULL;
		renderer = NULL;
		glContext = NULL;

		ScreenWidth = 0;
		ScreenHeight = 0;
	}
	~Display()
	{
		if (glContext != NULL)
			SDL_GL_DeleteContext(glContext);

		glContext = NULL;

		if (renderer != NULL)
			SDL_DestroyRenderer(renderer);

		renderer = NULL;

		if (window != NULL)
			SDL_DestroyWindow(window);

		window = NULL;
	}

	bool Create2D(std::string title, int w, int h, int flags, bool TargetTexture, bool VSYNC, float FPS)
	{
		is3D = false;

		window = NULL;
		window = CreateAndLogWindow(title.c_str(), w, h, flags);

		if (window == NULL)
		{
			LOG_ERROR("Couldn't create Window! Error: " << SDL_GetError());
			return false;
		}

		renderer = NULL;
		renderer = CreateAndLogRenderer(window, TargetTexture, VSYNC, FPS);

		if (renderer == NULL)
		{
			LOG_ERROR("Couldn't create Renderer! Error: " << SDL_GetError());
			return false;
		}

		LOG_PURE("Using 2D");
		Logger::Instance()->NewLine();

		return true;
	}
	bool Create3D(std::string title, int w, int h, int flags)
	{
		is3D = true;

		if (!ContainsFlag(flags, SDL_WINDOW_OPENGL))
		{
			LOG_ERROR("Flag must contain SDL_WINDOW_OPENGL if using 3D!");
			SDL_ShowSimpleMessageBox(0, "Error!", "Flag must contain SDL_WINDOW_OPENGL if using 3D!", NULL);
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		window = NULL;
		window = CreateAndLogWindow(title.c_str(), w, h, flags);

		if (window == NULL)
		{
			LOG_ERROR("Couldn't create Window! Error: " << SDL_GetError());
			return false;
		}

		glContext = NULL;
		glContext = SDL_GL_CreateContext(window);

		if (glContext == NULL)
		{
			LOG_ERROR("Couldn't create glContext! Error: " << SDL_GetError());
			return false;
		}

		LOG_PURE("OpenGL Version: " << glGetString(GL_VERSION));
		LOG_PURE("GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION));

		glEnable(GL_DEPTH_TEST);

		LOG_PURE("Using 3D");
		Logger::Instance()->NewLine();

		return true;
	}

	Rect& GetSize()
	{		
		SDL_GetWindowSize(window, &ScreenWidth, &ScreenHeight);

		ScreenPos.SetPosition(0, 0, ScreenWidth, ScreenHeight);

		return ScreenPos;
	}
	int& GetW()
	{
		SDL_GetWindowSize(window, &ScreenWidth, NULL);
		return ScreenWidth;
	}
	int& GetH()
	{
		SDL_GetWindowSize(window, NULL, &ScreenHeight);
		return ScreenHeight;
	}

	SDL_Window* GetWindow()
	{
		return window;
	}
	SDL_Renderer* GetRenderer()
	{
		return renderer;
	}

	void Clear()
	{
		if (is3D)
		{
			glClearColor((float)(color.r / 255), (float)(color.g / 255), (float)(color.b / 255), (float)(color.a / 255));
			//TODO: Add Other buffers to clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		else
		{
			if (renderer != NULL)
				SDL_RenderClear(renderer);
		}
	}
	void Present()
	{
		if (is3D)
		{
			SDL_GL_SwapWindow(window);
		}
		else
		{
			if (renderer != NULL)
				SDL_RenderPresent(renderer);
		}
	}

	void SetRenderColor(Color color)
	{
		this->color = color;

		if (renderer != NULL)
		{
			if (SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a) != 0)
			{
				LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
			}
		}
	}
	void SetRenderColor(SDL_Color color)
	{
		this->color = color;
		
		if (renderer != NULL)
		{
			if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
			{
				LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
			}
		}
	}
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b)
	{
		color.SetColor(r, g, b, 255);

		if (renderer != NULL)
		{
			if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255) != 0)
			{
				LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
			}
		}
	}
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		color.SetColor(r, g, b, a);

		if (renderer != NULL)
		{
			if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a) != 0)
			{
				LOG_ERROR("Couldn't set Render Draw Color! Error: " << SDL_GetError());
			}
		}
	}

	void PushRenderColor()
	{
		renderColorStack.push_back(color);
	}
	void PopRenderColor()
	{
		if (renderColorStack.size() > 0)
		{
			SetRenderColor(renderColorStack[renderColorStack.size() - 1]);
			renderColorStack.pop_back();
		}
		else
			LOG_DEBUG("Can't pop back render color because no render color is pushed to stack");
	}

	Color& GetRenderColor()
	{
		return color;
	}

	bool Is3D()
	{
		return is3D;
	}

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