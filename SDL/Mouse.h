//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>
#include <map>

#include "Rect.h"

enum Scroll
{
	SDL_MOUSESCROLL_UP = 0,
	SDL_MOUSESCROLL_DOWN = 1
};

class Mouse
{
public:
	Mouse(SDL_Event *event);

	bool IsHover(Rect& pos);

	bool IsButtonPressed(Uint8 button);
	bool IsButtonReleased(Uint8 button);

	bool OnButtonPress(Uint8 button);
	bool OnButtonRelease(Uint8 button);

	bool IsWheelScrolled(Scroll scroll);

	int GetScroll();

	void SetMouseVisible(bool visible);

	void Clear();

	void Update();

	Rect& GetPosition();

	int GetX();
	int GetY();

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