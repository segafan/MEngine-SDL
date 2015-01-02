//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include <SDL2/SDL.h>

class Keyboard
{
public:
	Keyboard(SDL_Event *event);

	bool IsKeyPressed(SDL_Keycode key);

	bool IsKeyReleased(SDL_Keycode key);

	bool OnKeyPress(SDL_Keycode key);

	void Clear();

	void Update();
private:
	SDL_Event *event;
	std::map<int, bool> keys;
	std::map<int, bool> keysPressed;
};

#endif