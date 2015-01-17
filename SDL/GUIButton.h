//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <string>

#include "Global.h"

class GUIButton
{
public:
	GUIButton(Global* global)
	{
		this->global = global;

		//Position stuff
		pos.SetPosition(0, 0, 100, 30);
		relPos = &global->display.GetSize();
		finalPos = pos + *relPos;

		//Enabled and visible
		enabled = true;
		visible = true;

		//Event stuff
		hover = false;
		clicked = false;

		//Font stuff
		font = "";
		fontSize = 12;

		//Text stuff
		text = "";
		textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY(), 0, 0);
		textColor.SetColor(0, 0, 0, 255);

		textColorOnHover.SetColor(0, 0, 0, 255);
		textColorOnClick.SetColor(0, 0, 0, 255);
	}

	void Update()
	{
		if (enabled)
		{
			//Calculate Pos
			finalPos = pos + *relPos;
			textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY(), 0, 0);

			//Mouse
			hover = false;
			clicked = false;

			if (global->input.mouse.IsHover(finalPos))
			{
				hover = true;
				//TODO: Which button needs to be pressed
				if (global->input.mouse.OnButtonPress(SDL_BUTTON_LEFT))
					clicked = true;
			}
		}
	}

	void Draw()
	{
		if (visible)
		{
			if (clicked)
				global->gfx.DrawText(font, fontSize, text, &textPos, textColorOnClick, ALIGN_CENTER);
			else if (hover)
				global->gfx.DrawText(font, fontSize, text, &textPos, textColorOnHover, ALIGN_CENTER);
			else
				global->gfx.DrawText(font, fontSize, text, &textPos, textColor, ALIGN_CENTER);
		}
	}
	
	//Bool Functions
	bool OnClick()
	{
		return clicked;
	}
	bool OnHover()
	{
		return hover;
	}

	//Setters

	//Position Setters
	void SetPosition(Rect pos)
	{
		this->pos = pos;
		finalPos = pos + *relPos;
		textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY(), 0, 0);
	}
	void SetPositionRelativeTo(Rect* relPos)
	{
		this->relPos = relPos;
	}

	//Font Setters
	void SetFont(std::string key, int size)
	{
		if (global->gfx.GetFont(key, size) == NULL)
		{
			LOG_ERROR("Couldn't set font in button, ", "Font key: ", key, "Font Size: ", size);
			LOG_ERROR("It's probably not loaded with that key and size combination!");
			return;
		}
		
		font = key;
		fontSize = size;
	}

	//Text Setters
	void SetText(std::string text)
	{
		this->text = text;
	}
	void SetTextColor(Color color)
	{
		this->textColor = color;
	}
	void SetTextColorOnHover(Color color)
	{
		this->textColorOnHover = color;
	}
	void SetTextColorOnClick(Color color)
	{
		this->textColorOnClick = color;
	}

	//Enabled and visible Setters
	void SetEnabled(bool enabled)
	{
		this->enabled = enabled;
	}
	void SetVisible(bool visible)
	{
		this->visible = visible;
	}
	void SetEnabledAndVisible(bool EnabledAndVisible)
	{
		this->enabled = EnabledAndVisible;
		this->visible = EnabledAndVisible;
	}
	
	//TODO: Add name to every button
private:
	//Global
	Global* global;

	//Enabled and visible
	bool enabled;
	bool visible;

	//Event stuff
	bool hover;
	bool clicked;

	//Position
	Rect pos;
	Rect* relPos;
	Rect finalPos;

	//Font stuff
	std::string font;
	int fontSize;

	//Text stuff
	Rect textPos;
	std::string text;
	Color textColor;

	Color textColorOnHover;
	Color textColorOnClick;
};

#endif