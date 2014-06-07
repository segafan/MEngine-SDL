#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SDL.h>

#include <map>
#include <string>

#include "Keyboard.h"

class TextInput
{
public:
	TextInput(SDL_Event* event, Keyboard* keyboard)
	{
		this->event = event;
		this->keyboard = keyboard;
	}

	void Update()
	{
		typedef std::map<std::string, bool>::iterator it_type;

		for (it_type iterator = active.begin(); iterator != active.end(); iterator++)
		{
			if (active[iterator->first])
			{
				if ((keyboard->IsKeyPressed(SDLK_LCTRL) || keyboard->IsKeyPressed(SDLK_RCTRL)) && keyboard->IsKeyPressed(SDLK_v))
				{
					//TODO: This may cause a memory leak SDL_GetClipboardText()
					if (SDL_HasClipboardText())
					{
						text[iterator->first] += SDL_GetClipboardText();
					}
				}

				if (event->type == SDL_TEXTINPUT)
					text[iterator->first] += event->text.text;
				if (keyboard->IsKeyPressed(SDLK_BACKSPACE) && text[iterator->first].size() > 0)
					text[iterator->first].pop_back();
			}
		}
	}

	bool AddTextInput(std::string key)
	{
		if (key == "")
		{
			//TODO: Log this
			std::cout << "You must set a key in Text Input!" << std::endl;
			return false;
		}

		if (text.count(key) != 0)
		{
			//TODO: Log this
			std::cout << "There is already a Text Input with this key: " << key << std::endl;
			return false;
		}

		text[key] = "";
		active[key] = false;

		return true;
	}

	void SetTextInputActive(std::string key, bool isActive)
	{
		if (text.count(key) == 0)
		{
			//TODO: Log this
			std::cout << "There isn't a Text Input with this key, so can't set active! key: " << key << std::endl;
			
			//Create it so it won't show this message later
			text[key] = "";
			active[key] = false;
			return;
		}

		active[key] = isActive;
	}

	std::string& GetText(std::string key)
	{
		if (text.count(key) == 0)
		{
			//TODO: Log this
			std::cout << "There isn't a Text Input with this key, so can't get text! key: " << key << std::endl;
			
			//Create it so it won't show this message later
			text[key] = "";
			active[key] = false;
			return text[key];
		}

		return text[key];
	}

	void SetText(std::string key, std::string textToSet)
	{
		if (text.count(key) == 0)
		{
			//TODO: Log this
			std::cout << "There isn't a Text Input with this key, so can't set text! key: " << key << std::endl;

			//Create it so it won't show this message later
			text[key] = "";
			active[key] = false;
			return;
		}

		text[key] = textToSet;
	}

private:
	//Events
	SDL_Event* event;
	Keyboard* keyboard;

	//Text Input Stuff
	std::map<std::string, std::string> text;
	std::map<std::string, bool> active;
};

#endif