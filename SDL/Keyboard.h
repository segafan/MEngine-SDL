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

	bool OnKeyPress(SDL_Keycode key)
	{
		return keysPressed[key];
	}

	void Clear()
	{
		typedef std::map<int, bool>::iterator it_type;

		for (it_type it = keysPressed.begin(); it != keysPressed.end(); it++)
		{
			keysPressed[it->first] = false;
		}
	}

	void Update()
	{
		//Normal Key Input
		if (event->type == SDL_KEYDOWN)
		{
			keys[event->key.keysym.sym] = true;

			if (!(event->key.repeat > 0))
			keysPressed[event->key.keysym.sym] = true;
		}
		if (event->type == SDL_KEYUP)
		{
			keys[event->key.keysym.sym] = false;
		}
	}
private:
	SDL_Event *event;
	std::map<int, bool> keys;
	std::map<int, bool> keysPressed;

	std::map<int, bool> keysPressedOnce;
	std::map<int, int> repeat;
};

#endif