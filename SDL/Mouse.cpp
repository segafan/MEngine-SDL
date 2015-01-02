#include "Mouse.h"

Mouse::Mouse(SDL_Event *event)
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

bool Mouse::IsHover(Rect& pos)
{
	return pos.Intersects(rect);
}

bool Mouse::IsButtonPressed(Uint8 button)
{
	return buttons[button];
}

bool Mouse::IsButtonReleased(Uint8 button)
{
	return !buttons[button];
}

bool Mouse::OnButtonPress(Uint8 button)
{
	return buttonsDown[button];
}

bool Mouse::OnButtonRelease(Uint8 button)
{
	return buttonsUp[button];
}

bool Mouse::IsWheelScrolled(Scroll scroll)
{
	if (scroll == SDL_MOUSESCROLL_UP)
		return scrollUp;
	if (scroll == SDL_MOUSESCROLL_DOWN)
		return scrollDown;
}

int Mouse::GetScroll()
{
	return scroll;
}

void Mouse::SetMouseVisible(bool visible)
{
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}

void Mouse::Clear()
{
	buttonsUp.clear();
	buttonsDown.clear();
}

void Mouse::Update()
{
	//Mouse Position
	SDL_GetMouseState(&x, &y);

	//Mouse Rect
	rect.SetPosition(x, y, 1, 1);

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

Rect& Mouse::GetPosition()
{
	return rect;
}

int Mouse::GetX()
{
	return x;
}

int Mouse::GetY()
{
	return x;
}
