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

	void Update();

	bool AddTextInput(std::string key);

	void SetTextInputActive(std::string key, bool isActive);

	std::string& GetText(std::string key);

	void SetText(std::string key, std::string textToSet);

private:
	//Events
	SDL_Event* event;
	Keyboard* keyboard;

	//Text Input Stuff
	std::map<std::string, std::string> text;
	std::map<std::string, bool> active;
};

#endif