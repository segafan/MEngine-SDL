#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include <map>
#include <string>

#include "Global.h"

class GUIButton
{
public:
	GUIButton(Global* global)
	{
		this->global = global;

		text = "";
		pos.SetPosition(0, 0, 100, 30);
	}

	void Update()
	{
		hover = false;
		clicked = false;

		if (global->input.mouse.IsHover(pos))
		{
			//TODO: Which button needs to be pressed
			if (global->input.mouse.IsButtonPressed(SDL_BUTTON_LEFT))
				clicked = true;
			else
				hover = true;
		}
		
	}

	void Draw()
	{
		if (clicked)
		{
			global->screen.SetRenderColor(255, 0, 255);
		}
		else if (hover)
		{
			global->screen.SetRenderColor(0, 255, 0);
		}
		else
		{
			global->screen.SetRenderColor(255, 0, 0);
		}
		
		SDL_RenderFillRect(global->screen.GetRenderer(), pos.ToSDLRect());

		global->gfx.DrawText(font, fontSize, text, &pos, textColor);

		global->screen.SetRenderColor(255, 255, 0);
	}
	
	//Setters
	void SetFont(std::string key, int size)
	{
		if (global->gfx.GetFont(key, size) == NULL)
		{
			global->logger.LogLine("Couldn't set font in button, ", "Font key: ", key, "Font Size: ", size);
			global->logger.LogLine("It's probably not loaded with that key and size combination!");
			return;
		}
		
		font = key;
	}
	void SetText(std::string text)
	{
		this->text = text;
	}

private:
	//Global
	Global* global;

	bool hover;
	bool clicked;

	Rect pos;

	//Button Text stuff
	std::string font;
	int fontSize;

	std::string text;
	Color textColor;
};

#endif