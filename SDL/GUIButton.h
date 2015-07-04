//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <string>

#include "Global.h"

class GUIButton
{
public:
	GUIButton()
	{
		//Position stuff
		pos.SetPosition(0, 0, 100, 30);
		relPos.SetPosition(0, 0, 0, 0);
		finalPos = pos + relPos;

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

	void Update(Global* global)
	{
		if (enabled)
		{
			//Calculate Pos
			finalPos = pos + relPos;
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

	void Draw(Global* global)
	{
		if (visible)
		{
			if (global->gfx.GetFont(font, fontSize) == NULL)
			{
				LOG_ERROR("Couldn't use font in button, " << "Font key: " << font << "Font Size: ", fontSize);
				LOG_ERROR("It's probably not loaded with that key and size combination!");
				return;
			}

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
		finalPos = pos + relPos;
		textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY(), 0, 0);
	}
	void SetPositionRelativeTo(Rect relPos)
	{
		this->relPos = relPos;
	}

	//Font Setters
	void SetFont(std::string key, int size)
	{
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
	
	//Getters

	//Position Getters
	Rect GetPosition()
	{
		return pos;
	}
	Rect GetPositionRelativeTo()
	{
		return relPos;
	}

	//Font Getters
	std::string GetFontName()
	{
		return font;
	}
	int GetFontSize()
	{
		return fontSize;
	}

	//Text Getters
	std::string GetText()
	{
		return text;
	}
	Color GetTextColor()
	{
		return textColor;
	}
	Color GetTextColorOnHover()
	{
		return textColorOnHover;
	}
	Color GetTextColorOnClick()
	{
		return textColorOnClick;
	}

	//Enabled and visible Getters
	bool GetEnabled()
	{
		return enabled;
	}
	bool GetVisible()
	{
		return visible;
	}

private:
	//Enabled and visible
	bool enabled;
	bool visible;

	//Event stuff
	bool hover;
	bool clicked;

	//Position
	Rect pos;
	Rect relPos;
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