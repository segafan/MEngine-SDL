#ifndef FONT_H
#define FONT_H

#include <string>
#include <SDL2/SDL_ttf.h>

#include "Logger.h"
#include "Display.h"

enum CharSet
{
	ASCII_STANDARD = 128,
	ASCII_EXTENDED = 256,
	UTF16 = 65536
};

class Font
{
public:
	Font();
	Font(Display* display, const std::string& filepath, unsigned int size);
	Font(Display* display, const std::string& filepath, unsigned int size, int numchar);
	~Font();

	void Load(Display* display, const std::string& filepath, unsigned int size);
	void Load(Display* display, const std::string& filepath, unsigned int size, int numchar);
	void Destroy();

	bool IsEmpty();

	std::vector<Rect>& GetGlyphPositions();
	SDL_Texture* GetBitmapFont();

private:
	void ConvertToBitmapFont(Display* display, int numchar);

	int size;

	std::vector<Rect> glyphPositions;
	SDL_Texture* bitmapFont;
	TTF_Font* font;
};

#endif