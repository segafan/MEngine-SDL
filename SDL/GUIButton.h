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
		font = 0;

		//Text stuff
		text = L"";
		textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY(), 0, 0);
		textColor.SetColor(0, 0, 0, 255);

		textColorOnHover.SetColor(0, 0, 0, 255);
		textColorOnClick.SetColor(0, 0, 0, 255);
	}

	void Update(Global* global)
	{
		if (enabled)
		{
			if (cropToText)
			{
				if (global->gfx.GetFont(font) != NULL)
				{
					Rect textSize = global->gfx.GetFont(font)->GetTextSize(text);
					pos.SetW(textSize.GetW());
					pos.SetH(textSize.GetH());
				}
			}

			//Calculate Pos
			finalPos = pos + relPos;
			
			if (global->gfx.GetFont(font) != NULL)
				textPos.SetPosition(finalPos.CenterX(), finalPos.CenterY() - global->gfx.GetFont(font)->GetGlyphHeight() / 2, 0, 0);
			else
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
			if (global->gfx.GetFont(font) == NULL)
			{
				LOG_ERROR("Couldn't use font in button, " << "Font key: " << font);
				LOG_ERROR("It's probably not loaded with that key and size combination!");
				return;
			}

			if (clicked)
				global->display.DrawText(global->gfx.GetFont(font), text, &textPos, textColorOnClick, ALIGN_CENTER);
			else if (hover)
				global->display.DrawText(global->gfx.GetFont(font), text, &textPos, textColorOnHover, ALIGN_CENTER);
			else
				global->display.DrawText(global->gfx.GetFont(font), text, &textPos, textColor, ALIGN_CENTER);
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
	void SetFont(unsigned int key)
	{
		font = key;
	}

	//Text Setters
	void SetText(std::wstring text)
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
	void CropToText(bool cropToText)
	{
		this->cropToText = cropToText;
	}
	void SetCenter(Point point)
	{
		pos.SetX(point.getX() - (pos.GetW() / 2));
		pos.SetY(point.getY() - (pos.GetH() / 2));
	}
	void SetCenter(int x, int y)
	{
		pos.SetX(x - (pos.GetW() / 2));
		pos.SetY(y - (pos.GetH() / 2));
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
	unsigned int GetFont()
	{
		return font;
	}

	//Text Getters
	std::wstring GetText()
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
	bool cropToText;

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
	unsigned int font;

	//Text stuff
	Rect textPos;
	std::wstring text;
	Color textColor;

	Color textColorOnHover;
	Color textColorOnClick;
};

#endif