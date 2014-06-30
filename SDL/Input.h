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

static bool PollEvent(Input* input)
{
	//TODO: Do something so this is not static
	static bool clearSinglePressData = true;

	if (clearSinglePressData)
	{
		input->keyboard.Clear();
		clearSinglePressData = false;
	}

	if (SDL_PollEvent(&input->event) > 0)
	{
		input->mouse.Update();
		input->keyboard.Update();
		input->text.Update();

		return true;
	}
	else
	{
		clearSinglePressData = true;
		return false;
	}
}

#endif