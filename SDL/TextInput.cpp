#include "TextInput.h"

TextInput::TextInput(SDL_Event* event, Keyboard* keyboard)
{
	this->event = event;
	this->keyboard = keyboard;
}

void TextInput::Clear()
{
	text = "";
	backspace = false;
	right = false;
	left = false;
}

void TextInput::Update()
{
	if ((keyboard->IsKeyPressed(SDLK_LCTRL) || keyboard->IsKeyPressed(SDLK_RCTRL)) && keyboard->IsKeyPressed(SDLK_v))
	{
		if (SDL_HasClipboardText())
		{
			char* clipboard_text = SDL_GetClipboardText();
				text.append(clipboard_text);
				SDL_free(clipboard_text);
		}
	}

	if (event->type == SDL_TEXTINPUT)
		text.append(event->text.text);
	if (keyboard->IsKeyPressed(SDLK_BACKSPACE))
		backspace = true;
	if (keyboard->IsKeyPressed(SDLK_RIGHT))
		right = true;
	if (keyboard->IsKeyPressed(SDLK_LEFT))
		left = true;
}

std::string& TextInput::GetText()
{
	return text;
}

bool TextInput::IsBackSpace()
{
	return backspace;
}

bool TextInput::IsRight()
{
	return right;
}

bool TextInput::IsLeft()
{
	return left;
}