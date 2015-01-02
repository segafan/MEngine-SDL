//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef INPUT_H
#define INPUT_H

#include "Keyboard.h"
#include "Mouse.h"

#include "TextInput.h"

class Input
{
public:
	Input()
		: event()
		, mouse(&event)
		, keyboard(&event)
		, text(&event, &keyboard)
	{
	}

	SDL_Event event;
	Mouse	  mouse;
	Keyboard  keyboard;
	TextInput text;
};

bool PollEvent(Input* input);

#endif