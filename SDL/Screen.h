#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>

class WindowScreen
{
public:
	WindowScreen(SDL_Window *window, SDL_Renderer *renderer)
	{
		this->window = window;
		this->renderer = renderer;

		GetScreenSize();
	}

	Rect* GetScreenSize()
	{		
		SDL_GetWindowSize(window, &ScreenWidth, &ScreenHeight);

		ScreenPos.SetPosition(0, 0, ScreenWidth, ScreenHeight);

		return &ScreenPos;
	}

	SDL_Window* GetWindow()
	{
		return window;
	}
	SDL_Renderer* GetRenderer()
	{
		return renderer;
	}

private:
	SDL_Window *window;
	SDL_Renderer *renderer;

	int ScreenWidth;
	int ScreenHeight;
	
	Rect ScreenPos;
};

#endif