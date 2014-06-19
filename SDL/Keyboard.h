#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include <SDL2/SDL.h>

class Keyboard
{
public:
	Keyboard(SDL_Event *event)
	{
		this->event = event;

		keys[event->key.keysym.sym] = false;
		
		repeat[event->key.keysym.sym] = 0;
		keysPressedOnce[event->key.keysym.sym] = false;
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
			if (repeat[key] == 0)
				keysPressedOnce[key] = true;
			else
				keysPressedOnce[key] = false;

			repeat[key]++;
		}
		else if (IsKeyReleased(key))
		{
			repeat[key] = 0;
			keysPressedOnce[key] = false;
		}

		return keysPressedOnce[key];
	}

	bool IsKeyPressedOnce(SDL_Keycode key, unsigned int interval)
	{
		if (IsKeyPressed(key))
		{
			if (repeat[key] == 0)
				keysPressedOnce[key] = true;
			else
				keysPressedOnce[key] = false;

			if (repeat[key] % interval == 0)
				keysPressedOnce[key] = true;

			repeat[key]++;
		}
		else if (IsKeyReleased(key))
		{
			repeat[key] = 0;
			keysPressedOnce[key] = false;
		}

		return keysPressedOnce[key];
	}

	void Update()
	{
		//Normal Key Input
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

	std::map<int, bool> keysPressedOnce;
	std::map<int, int> repeat;
};

#endif