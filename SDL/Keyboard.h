//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>

#include <unordered_map>

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
	std::unordered_map<int, bool> keys;
	std::unordered_map<int, bool> keysPressed;
};

#endif