//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Util.h"
#include "Rect.h"
#include "Logger.h"
#include "Display.h"
#include "Font.h"

#include <vector>

class FontManager
{
public:
	FontManager();
	~FontManager();

	//Add & Destroy Fonts
	void AddFont(Display* display, std::string filepath, unsigned int key, unsigned int size);
	void AddFont(Display* display, std::string filepath, unsigned int key, unsigned int size, unsigned int numchar);
	void RemoveFont(unsigned int key);

	Font* GetFont(unsigned int key);

	void Clear();

private:
	std::vector<Font*> fonts;
};

#endif