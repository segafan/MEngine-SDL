#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

class Input
{
public:
	Input()
		: event()
		, mouse(&event)
		, keyboard(&event)
	{
	}

	SDL_Event event;
	Mouse	  mouse;
	Keyboard  keyboard;
};

#endif