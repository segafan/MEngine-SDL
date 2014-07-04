//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

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
		buttonsUp[event->button.button] = false;
		buttonsDown[event->button.button] = false;

		scroll = 0;

		scrollUp = false;
		scrollDown = false;

		x = 0;
		y = 0;
	}

	bool IsHover(Rect& pos)
	{
		return pos.Intersects(rect);
	}

	bool IsButtonPressed(Uint8 button)
	{
		return buttons[button];
	}
	bool IsButtonReleased(Uint8 button)
	{
		return !buttons[button];
	}

	bool OnButtonPress(Uint8 button)
	{
		return buttonsDown[button];
	}
	bool OnButtonRelease(Uint8 button)
	{
		return buttonsUp[button];
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

	void SetMouseVisible(bool visible)
	{
		if (visible)
			SDL_ShowCursor(1);
		else
			SDL_ShowCursor(0);
	}

	void Clear()
	{
		buttonsUp.clear();
		buttonsDown.clear();
	}

	void Update()
	{
		//Mouse Position
		SDL_GetMouseState(&x, &y);

		//Mouse Rect
		rect.SetPosition(x, y, 4, 4);

		//Mouse Buttons
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			buttons[event->button.button] = true;
			buttonsDown[event->button.button] = true;
		}
		if (event->type == SDL_MOUSEBUTTONUP)
		{
			buttons[event->button.button] = false;
			buttonsUp[event->button.button] = true;
		}

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

	Rect& GetPosition()
	{
		return rect;
	}

	int GetX() { return x; }
	int GetY() { return x; }

private:
	int x, y;

	Rect rect;

	SDL_Event *event;

	bool scrollUp;
	bool scrollDown;

	int scroll;

	std::map<int, bool> buttons;
	std::map<int, bool> buttonsUp;
	std::map<int, bool> buttonsDown;
};

#endif