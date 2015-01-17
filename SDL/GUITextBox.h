//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GUITEXTBOX_H
#define GUITEXTBOX_H

#include <string>

#include "Global.h"

class GUITextBox
{
public:
	GUITextBox(Global *global, std::string nameOfTextBox)
	{
		this->global = global;

		this->name = nameOfTextBox;

		//Calculate Name of Text Input
		if (!global->input.text.AddTextInput(name))
		{
			LOG_DEBUG("There is already a button with this name! Name: ", name);
			return;
		}

		//Position stuff
		pos.SetPosition(0, 0, 200, 30);
		relPos = &global->display.GetSize();
		finalPos = pos + *relPos;

		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY(), 0, 0);

		//Event Stuff
		focus = false;

		//Font Stuff
		font = "FONT";
		fontSize = 12;

		//Text Stuff
		text = "";
		textLength = 20;
	}

	void Update()
	{
		//Calculate Position
		finalPos = pos + *relPos;
		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY(), 0, 0);

		//Mouse Stuff
		if (global->input.mouse.IsHover(finalPos))
		{
			if (global->input.mouse.IsButtonPressed(SDL_BUTTON_LEFT))
				focus = true;
		}
		else
			if (global->input.mouse.IsButtonPressed(SDL_BUTTON_LEFT))
				focus = false;

		if (focus)
		{
			//TODO: Text Input here
			global->input.text.SetTextInputActive(name, true);
			text = global->input.text.GetText(name);
		}
		else
			global->input.text.SetTextInputActive(name, false);

		//Text Length Calculations
		if (text.size() > textLength)
		{
			text = text.substr(0, textLength);
			global->input.text.SetText(name, text);
		}
	}

	void Draw()
	{
		global->display.SetRenderColor(255, 255, 255);
		SDL_RenderFillRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(0, 0, 0);
		SDL_RenderDrawRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(255, 255, 0);

		global->gfx.DrawText(font, fontSize, text, &textPos, MapRGB(0, 0, 0), ALIGN_CENTER_Y);
	}

	bool IsFocus()
	{
		return focus;
	}

	//Setters

	void SetFocus(bool focus)
	{
		this->focus = focus;
	}

	//Position
	void SetPosition(Rect pos)
	{
		this->pos = pos;
	}
	void SetPositionRelativeTo(Rect* relPos)
	{
		this->relPos = relPos;
	}

	//Font Stuff
	void SetFont(std::string key, int size)
	{
		if (global->gfx.GetFont(key, size) == NULL)
		{
			LOG_ERROR("Couldn't set font in textbox, ", "Font key: ", key, "Font Size: ", size);
			LOG_ERROR("It's probably not loaded with that key and size combination!");
			return;
		}

		font = key;
		fontSize = size;
	}

	//Text Stuff
	void SetText(std::string text)
	{
		this->text = text;
	}

	//Getters

	std::string GetText()
	{
		return text;
	}

private:
	//Global
	Global *global;

	//Name
	std::string name;

	//Position Stuff
	Rect pos;
	Rect* relPos;
	Rect finalPos;

	//Event Stuff
	bool focus;

	//Font stuff
	std::string font;
	int fontSize;

	//Text Stuff
	std::string text;
	unsigned int textLength;
	Rect textPos;
};

#endif