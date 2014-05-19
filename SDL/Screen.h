#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

#include "Color.h"

class WindowScreen
{
public:
	WindowScreen(SDL_Window *window, SDL_Renderer *renderer)
	{
		this->window = window;
		this->renderer = renderer;
	}
	~WindowScreen()
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;

		SDL_DestroyWindow(window);
		window = NULL;
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

	void RenderClear()
	{
		SDL_RenderClear(renderer);
	}
	void RenderPresent()
	{
		SDL_RenderPresent(renderer);
	}

	void SetRenderColor(Color color)
	{
		this->color = color;

		if (SDL_SetRenderDrawColor(renderer, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a) != 0)
		{
			//TODO: Log error
		}
	}
	void SetRenderColor(SDL_Color color)
	{
		this->color = color;
		
		if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
		{
			//TODO: Log error
		}
	}
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b)
	{
		color.SetColor(r, g, b, 255);

		if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255) != 0)
		{
			//TODO: Log error
		}
	}
	void SetRenderColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		color.SetColor(r, g, b, a);

		if (SDL_SetRenderDrawColor(renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a) != 0)
		{
			//TODO: Log error
		}
	}

	Color& GetRenderColor()
	{
		return color;
	}

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	int ScreenWidth;
	int ScreenHeight;
	
	Color color;
	Rect ScreenPos;
};

#endif