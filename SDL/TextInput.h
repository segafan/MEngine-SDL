//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

#include "Logger.h"
#include "Keyboard.h"

class TextInput
{
public:
	TextInput(SDL_Event* event, Keyboard* keyboard);

	void Clear();
	void Update();

	std::string& GetText();
	bool IsBackSpace();
	bool IsRight();
	bool IsLeft();

private:
	//Events
	SDL_Event* event;
	Keyboard* keyboard;

	//Text Input Stuff
	std::string text;
	bool backspace;
	bool right;
	bool left;
};

#endif