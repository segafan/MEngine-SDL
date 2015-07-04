//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GUITEXTBOX_H
#define GUITEXTBOX_H

#include <string>

#include "Global.h"

class GUITextBox
{
public:
	GUITextBox()
	{
		//Position stuff
		pos.SetPosition(0, 0, 200, 30);
		relPos = Rect(0, 0, 0, 0);
		finalPos = pos + relPos;

		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY(), 0, 0);

		//Event Stuff
		focus = false;

		//Font Stuff
		font = 0;
		fontSize = 12;

		//Text Stuff
		text = "";
		textLength = 20;
	}

	void Update(Global* global)
	{
		//Calculate Position
		finalPos = pos + relPos;
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
			text.append(global->input.text.GetText());

			if (global->input.text.IsBackSpace() && !text.empty())
				text.pop_back();
		}

		//Text Length Calculations
		if (text.size() > textLength)
			text = text.substr(0, textLength);
	}

	void Draw(Global* global)
	{
		global->display.SetRenderColor(255, 255, 255);
		SDL_RenderFillRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(0, 0, 0);
		SDL_RenderDrawRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(255, 255, 0);

		if (global->gfx.GetFont(font, fontSize) == NULL)
		{
			LOG_ERROR("Couldn't use font in textbox, " << "Font key: " << font << "Font Size: " << fontSize);
			LOG_ERROR("It's probably not loaded with that key and size combination!");
			return;
		}

		global->display.DrawText(global->gfx.GetFont(font, fontSize), text, &textPos, MapRGB(0, 0, 0), ALIGN_CENTER_Y);
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
	void SetPositionRelativeTo(Rect relPos)
	{
		this->relPos = relPos;
	}

	//Font Stuff
	void SetFont(unsigned int key, int size)
	{
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

	unsigned int GetFont()
	{
		return font;
	}

	unsigned int GetFontSize()
	{
		return fontSize;
	}

private:

	//Position Stuff
	Rect pos;
	Rect relPos;
	Rect finalPos;

	//Event Stuff
	bool focus;

	//Font stuff
	unsigned int font;
	int fontSize;

	//Text Stuff
	std::string text;
	unsigned int textLength;
	Rect textPos;
};

#endif