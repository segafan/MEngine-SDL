#ifndef MOUSE_H
#define MOUSE_H

#include <SDL.h>

class Mouse
{
public:
	Mouse(SDL_Event *event)
	{
		this->event = event;

		left = false;
		right = false;

		x = 0;
		y = 0;
	}

	bool isLeftPressed()
	{
		return left;
	}
	bool isRightPressed()
	{
		return right;
	}

	void Update()
	{
		SDL_GetMouseState(&x, &y);

		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (event->button.button == SDL_BUTTON_LEFT)
				left = true;
			if (event->button.button == SDL_BUTTON_RIGHT)
				right = true;
		}
		if (event->type == SDL_MOUSEBUTTONUP)
		{
			if (event->button.button == SDL_BUTTON_LEFT)
				left = false;
			if (event->button.button == SDL_BUTTON_RIGHT)
				right = false;
		}
	}

	int x, y;
private:
	SDL_Event *event;
	bool left;
	bool right;
};

#endif