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

	std::vector<Rect>& GetGlyphPositions();
	SDL_Texture* GetBitmapFont();

private:
	void ConvertToBitmapFont(Display* display);

	int size;

	std::vector<Rect> glyphPositions;
	SDL_Texture* bitmapFont;
	TTF_Font* font;
};

#endif