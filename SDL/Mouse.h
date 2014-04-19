#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

#include "Rect.h"

enum Scroll
{
	SDL_MOUSESCROLL_UP = 0,
	SDL_MOUSESCROLL_DOWN = 1
};

class Mouse
{
public:
	Mouse(SDL_Event *event)
	{
		this->event = event;

		buttons[event->button.button] = false;

		scroll = 0;

		scrollUp = false;
		scrollDown = false;

		x = 0;
		y = 0;
	}

	bool IsButtonPressed(Uint8 button)
	{
		return buttons[button];
	}
	bool IsButtonReleased(Uint8 button)
	{
		return !buttons[button];
	}

	bool IsWheelScrolled(Scroll scroll)
	{
		if (scroll == SDL_MOUSESCROLL_UP)
			return scrollUp;
		if (scroll == SDL_MOUSESCROLL_DOWN)
			return scrollDown;
	}

	int GetScroll()
	{
		return scroll;
	}

	void Update()
	{
		//Mouse Position
		SDL_GetMouseState(&x, &y);

		//Mouse Buttons
		if (event->type == SDL_MOUSEBUTTONDOWN)
			buttons[event->button.button] = true;
		if (event->type == SDL_MOUSEBUTTONUP)
			buttons[event->button.button] = false;

		//Scrolling
		scrollUp = false;
		scrollDown = false;

		if (event->type == SDL_MOUSEWHEEL)
		{
			if (event->button.x > 0)
			{
				scroll++;
				scrollUp = true;
			}
			if (event->button.x < 0)
			{
				scroll--;
				scrollDown = true;
			}
		}
	}

	Rect GetMouseRect()
	{
		return Rect::CreateRect(x, y, 4, 4);
	}

	int x, y;
private:
	SDL_Event *event;

	bool scrollUp;
	bool scrollDown;

	int scroll;

	std::map<int, bool> buttons;
};

#endif