#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include <SDL.h>

class Keyboard
{
public:
	Keyboard(SDL_Event *event)
	{
		this->event = event;

		keys[event->key.keysym.sym] = false;
	}

	bool IsKeyPressed(SDL_Keycode key)
	{
		return keys[key];
	}

	bool IsKeyReleased(SDL_Keycode key)
	{
		return !keys[key];
	}

	bool IsKeyPressedOnce(SDL_Keycode key)
	{
		if (IsKeyPressed(key))
		{
			if (keysAlreadyPressed[key])
				return false;
			else if (!keysAlreadyPressed[key])
			{
				keysAlreadyPressed[key] = true;
				return true;
			}
		}
		if (IsKeyReleased(key))
		{
			keysAlreadyPressed[key] = false;
		}
		
		return false;
	}

	void Update()
	{
		if (event->type == SDL_KEYDOWN)
		{
			keys[event->key.keysym.sym] = true;
		}
		if (event->type == SDL_KEYUP)
		{
			keys[event->key.keysym.sym] = false;
		}
	}
private:
	SDL_Event *event;
	std::map<int, bool> keys;

	std::map<int, bool> keysAlreadyPressed;
};

#endif