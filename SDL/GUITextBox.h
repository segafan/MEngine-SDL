//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GUITEXTBOX_H
#define GUITEXTBOX_H

#include <string>

#include "Global.h"

#include <locale>
#include <codecvt>
#include <string>

//TODO: Move this static variable to a .cpp file
static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

class GUITextBox
{
public:
	GUITextBox()
	{
		cursorPos = 0;

		//Position stuff
		pos.SetPosition(0, 0, 200, 30);
		relPos = Rect(0, 0, 0, 0);
		finalPos = pos + relPos;

		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY(), 0, 0);

		//Event Stuff
		focus = false;

		//Font Stuff
		font = 0;

		//Text Stuff
		text = L"";
		textLength = 20;
	}

	void Update(Global* global)
	{
		//Calculate Position
		finalPos = pos + relPos;

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
			text.append(converter.from_bytes(global->input.text.GetText()));

			if (global->input.text.IsBackSpace() && !text.empty())
				text.pop_back();
		}

		//Text Length Calculations
		if (text.size() > textLength)
			text = text.substr(0, textLength);
	}

	void Draw(Global* global)
	{
		global->display.PushRenderColor();

		global->display.SetRenderColor(255, 255, 255);
		SDL_RenderFillRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(0, 0, 0);
		SDL_RenderDrawRect(global->display.GetRenderer(), finalPos.ToSDLRect());

		global->display.PopRenderColor();

		if (global->gfx.GetFont(font) == NULL)
		{
			LOG_ERROR("Couldn't use font in textbox, " << "Font key: " << font);
			LOG_ERROR("It's probably not loaded with that key and size combination!");
			return;
		}

		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY() - global->gfx.GetFont(font)->GetTextSize(L"a").GetH() / 2, 0, 0);

		if (text != L"")
			global->display.DrawText(global->gfx.GetFont(font), text, &textPos, MapRGB(0, 0, 0), ALIGN_LEFT);
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
	void SetFont(unsigned int key)
	{
		font = key;
	}

	//Text Stuff
	void SetText(std::wstring text)
	{
		this->text = text;
	}

	void SetTextLength(unsigned int length)
	{
		this->textLength = length;
	}

	//Getters

	std::wstring GetText()
	{
		return text;
	}

	unsigned int GetFont()
	{
		return font;
	}

private:

	unsigned int cursorPos;

	//Position Stuff
	Rect pos;
	Rect relPos;
	Rect finalPos;

	//Event Stuff
	bool focus;

	//Font stuff
	unsigned int font;

	//Text Stuff
	std::wstring text;
	unsigned int textLength;
	Rect textPos;
};

#endif