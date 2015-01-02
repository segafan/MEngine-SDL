#include "Keyboard.h"

Keyboard::Keyboard(SDL_Event *event)
{
	this->event = event;

	keys[event->key.keysym.sym] = false;
	keysPressed[event->key.keysym.sym] = false;
}

bool Keyboard::IsKeyPressed(SDL_Keycode key)
{
	return keys[key];
}

bool Keyboard::IsKeyReleased(SDL_Keycode key)
{
	return !keys[key];
}

bool Keyboard::OnKeyPress(SDL_Keycode key)
{
	return keysPressed[key];
}

void Keyboard::Clear()
{
	keysPressed.clear();
}

void Keyboard::Update()
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
