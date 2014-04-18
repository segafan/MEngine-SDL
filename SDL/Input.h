#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

class Input
{
public:
	Input()
	{
		event =    new SDL_Event();
		mouse =	   new Mouse(event);
		keyboard = new Keyboard(event);
	}
	~Input()
	{
		delete event;
		delete keyboard;
		delete mouse;
	}

	SDL_Event *event;
	Mouse	  *mouse;
	Keyboard  *keyboard;
};

#endif