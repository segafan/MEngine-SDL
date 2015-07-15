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
		cursorTime = Time::GetTime();
		cursorBlinkRate = 0.530;

		selected = false;
		selectStart = 0;
		selectEnd = 0;

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
			if (global->input.mouse.OnButtonPress(SDL_BUTTON_LEFT))
				focus = true;
		}
		else
		{
			if (global->input.mouse.OnButtonPress(SDL_BUTTON_LEFT))
				focus = false;
		}

		if (focus)
		{
			std::wstring temp = converter.from_bytes(global->input.text.GetText());

			if (temp != L"")
			{
				if (selectStart - selectEnd != 0)
				{
					DeleteSelected();
				}
			}

			if (temp.length() + text.length() > textLength)
				temp = temp.substr(0, textLength - text.length());

			text.insert(cursorPos, temp);
			cursorPos += temp.length();
			
			if (global->gfx.GetFont(font) != NULL)
			{
				Point point(global->input.mouse.GetPosition().GetX() - textPos.GetX(), global->input.mouse.GetPosition().GetY() - textPos.GetY());
				if (global->input.mouse.OnButtonPress(SDL_BUTTON_LEFT))
				{
					int letter = global->gfx.GetFont(font)->GetLetterAt(text, point);
					selectStart = letter;
					selectEnd = letter;

					cursorTime = Time::GetTime() - (cursorBlinkRate + 0.001);
				}
				if (global->input.mouse.IsButtonPressed(SDL_BUTTON_LEFT))
				{
					int letter = global->gfx.GetFont(font)->GetLetterAt(text, point);
					selectEnd = letter;

					cursorPos = letter;
				}
			}
			//Control + C
			if ((global->input.keyboard.IsKeyPressed(SDLK_LCTRL) || global->input.keyboard.IsKeyPressed(SDLK_RCTRL)) && global->input.keyboard.IsKeyPressed(SDLK_c))
			{
				if (selectEnd - selectStart != 0)
				{
					if (selectEnd > selectStart)
						SDL_SetClipboardText(converter.to_bytes(text.substr(selectStart, selectEnd - selectStart)).c_str());
					else
						SDL_SetClipboardText(converter.to_bytes(text.substr(selectEnd, selectStart - selectEnd)).c_str());
				}
			}
			//Control + A
 			if ((global->input.keyboard.IsKeyPressed(SDLK_LCTRL) || global->input.keyboard.IsKeyPressed(SDLK_RCTRL)) && global->input.keyboard.IsKeyPressed(SDLK_a))
			{
				selectStart = 0;
				selectEnd = text.length();
				cursorPos = selectEnd;
			}
			//Control + X
			if ((global->input.keyboard.IsKeyPressed(SDLK_LCTRL) || global->input.keyboard.IsKeyPressed(SDLK_RCTRL)) && global->input.keyboard.IsKeyPressed(SDLK_x))
			{
				if (selectStart - selectEnd != 0)
				{
					//Put it on clipboard
					if (selectEnd > selectStart)
						SDL_SetClipboardText(converter.to_bytes(text.substr(selectStart, selectEnd - selectStart)).c_str());
					else
						SDL_SetClipboardText(converter.to_bytes(text.substr(selectEnd, selectStart - selectEnd)).c_str());

					//Delete it
					DeleteSelected();
				}
			}

			if (global->input.text.IsLeft() && cursorPos > 0)
			{
				cursorPos--;
				cursorTime = Time::GetTime() - (cursorBlinkRate + 0.001);
			}
			if (global->input.text.IsRight() && cursorPos < text.length())
			{
				cursorPos++;
				cursorTime = Time::GetTime() - (cursorBlinkRate + 0.001);
			}

			if (global->input.text.IsBackSpace() && !text.empty() && (cursorPos > 0 || selectStart - selectEnd != 0))
			{
				if (selectStart - selectEnd != 0)
				{
					DeleteSelected();
				}
				else
				{
					text.erase(cursorPos - 1, 1);
					cursorPos--;
				}
			}
		}
		
		//Text Length Calculations
		if (text.size() > textLength)
			text = text.substr(0, textLength);
	}

	void Draw(Global* global)
	{
		if (global->gfx.GetFont(font) == NULL)
		{
			LOG_ERROR("Couldn't use font in textbox, " << "Font key: " << font);
			LOG_ERROR("It's probably not loaded with that key and size combination!");
			return;
		}

		global->display.PushRenderColor();

		global->display.SetRenderColor(255, 255, 255);
		SDL_RenderFillRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		global->display.SetRenderColor(0, 0, 0);
		SDL_RenderDrawRect(global->display.GetRenderer(), finalPos.ToSDLRect());
		
		if (focus)
		{
			global->display.SetRenderColor(173, 214, 255);

			if (selectEnd - selectStart != 0)
			{
				Rect selectedRect;
				if (selectEnd > selectStart)
					selectedRect = global->gfx.GetFont(font)->GetTextSize(text.substr(selectStart, selectEnd - selectStart));
				else
					selectedRect = global->gfx.GetFont(font)->GetTextSize(text.substr(selectEnd, selectStart - selectEnd));

				Rect beginToSelectStart;
				if (selectEnd > selectStart)
					beginToSelectStart = global->gfx.GetFont(font)->GetTextSize(text.substr(0, selectStart));
				else
					beginToSelectStart = global->gfx.GetFont(font)->GetTextSize(text.substr(0, selectEnd));

				selectedRect.TranslateX(beginToSelectStart.GetW());

				SDL_RenderFillRect(global->display.GetRenderer(), (selectedRect + textPos).ToSDLRect());
			}
		}

		global->display.SetRenderColor(0, 0, 0);
		if (Time::GetTime() - cursorTime > cursorBlinkRate && focus)
		{
			int x = textPos.GetX() + global->gfx.GetFont(font)->GetTextSize(text.substr(0, cursorPos)).Right();
			SDL_RenderDrawLine(global->display.GetRenderer(), x, textPos.GetY(), x, textPos.GetY() + global->gfx.GetFont(font)->GetGlyphHeight());

			if (Time::GetTime() - cursorTime > (cursorBlinkRate * 2))
				cursorTime = Time::GetTime();
		}

		global->display.PopRenderColor();

		textPos.SetPosition(finalPos.GetX() + 9, finalPos.CenterY() - global->gfx.GetFont(font)->GetGlyphHeight() / 2, 0, 0);

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
	void DeleteSelected()
	{
		if (selectStart - selectEnd != 0)
		{
			if (selectEnd > selectStart)
			{
				text.erase(selectStart, selectEnd - selectStart);
				cursorPos = selectStart;
			}
			else
			{
				text.erase(selectEnd, selectStart - selectEnd);
				cursorPos = selectEnd;
			}
			selectStart = 0;
			selectEnd = 0;
		}
	}

	double cursorTime;
	double cursorBlinkRate;
	unsigned int cursorPos;

	bool selected;
	int selectStart;
	int selectEnd;

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