#ifndef FONT_H
#define FONT_H

#include <string>
#include <SDL2/SDL_ttf.h>

#include "Logger.h"
#include "Display.h"

class Font
{
public:
	Font();
	~Font();

	void Load(Display* display, const std::string& filepath, unsigned int size);
	void Destroy();

	bool IsEmpty();

	void Draw(Display* display, std::string text)
	{
		int x = 0;
		int y = 0;
		int h = glyphPositions[97].GetH();
		for (int i = 0; i < text.length(); i++)
		{
			if ((int)(text[i]) == 10)
			{
				y++;
				x = 0;
				continue;
			}

			Rect pos = glyphPositions[text[i]];
			pos.SetX(x);
			pos.SetY(y * h);
			x += pos.GetW();
			SDL_RenderCopy(display->GetRenderer(), bitmapFont, glyphPositions[text[i]].ToSDLRect(), pos.ToSDLRect());
		}
	}

private:
	void ConvertToBitmapFont(Display* display);

	int size;

	std::vector<Rect> glyphPositions;
	SDL_Texture* bitmapFont;
	TTF_Font* font;
};

#endif