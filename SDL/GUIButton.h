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
		global->screen.SetRenderColor(255, 255, 0);
	}

private:
	//Global
	Global* global;
	
	bool hover;
	bool clicked;

	Rect pos;

	std::string text;
};

#endif