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
		clearSinglePressData = true;
	}

	bool PollEvent();

	SDL_Event event;
	Mouse	  mouse;
	Keyboard  keyboard;
	TextInput text;

private:
	bool clearSinglePressData;
};


#endif