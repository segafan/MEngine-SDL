#include "TextInput.h"

TextInput::TextInput(SDL_Event* event, Keyboard* keyboard)
{
	this->event = event;
	this->keyboard = keyboard;
}

void TextInput::Update()
{
	typedef std::map<std::string, bool>::iterator it_type;

	for (it_type iterator = active.begin(); iterator != active.end(); iterator++)
	{
		if (active[iterator->first])
		{
			if ((keyboard->IsKeyPressed(SDLK_LCTRL) || keyboard->IsKeyPressed(SDLK_RCTRL)) && keyboard->IsKeyPressed(SDLK_v))
			{
				if (SDL_HasClipboardText())
				{
					char* clipboard_text = SDL_GetClipboardText();
					text[iterator->first] += clipboard_text;
					SDL_free(clipboard_text);
				}
			}

			if (event->type == SDL_TEXTINPUT)
				text[iterator->first] += event->text.text;
			if (keyboard->IsKeyPressed(SDLK_BACKSPACE) && text[iterator->first].size() > 0)
				text[iterator->first] = text[iterator->first].substr(0, text[iterator->first].size() - 1);
		}
	}
}

bool TextInput::AddTextInput(std::string key)
{
	if (key == "")
	{
		LOG_ERROR("You must set a key in Text Input!");
		return false;
	}

	if (text.count(key) != 0)
	{
		LOG_DEBUG("There is already a Text Input with this key: " << key);
		return false;
	}

	text[key] = "";
	active[key] = false;

	return true;
}

void TextInput::SetTextInputActive(std::string key, bool isActive)
{
	if (text.count(key) == 0)
	{
		LOG_ERROR("There isn't a Text Input with this key, so can't set it active! key: " << key);

		//Create it so it won't show this message later
		text[key] = "";
		active[key] = false;
		return;
	}

	active[key] = isActive;
}

std::string& TextInput::GetText(std::string key)
{
	if (text.count(key) == 0)
	{
		LOG_ERROR("There isn't a Text Input with this key, so can't get text! key: " << key);

		//Create it so it won't show this message later
		text[key] = "";
		active[key] = false;
		return text[key];
	}

	return text[key];
}

void TextInput::SetText(std::string key, std::string textToSet)
{
	if (text.count(key) == 0)
	{
		LOG_ERROR("There isn't a Text Input with this key, so can't set text! key: " << key);

		//Create it so it won't show this message later
		text[key] = "";
		active[key] = false;
		return;
	}

	text[key] = textToSet;
}
