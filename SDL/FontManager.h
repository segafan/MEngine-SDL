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

#include "Camera.h"

#include <unordered_map>

class FontManager
{
public:
	FontManager(Display* display);
	~FontManager();

	//Add & Destroy Fonts
	void AddFont(std::string filepath, unsigned int key, int size);
	void AddFont(TTF_Font* font, unsigned int key, int size);
	void RemoveFont(unsigned int key, int size);

	TTF_Font* GetFont(unsigned int key, int size);

	void Clear();

private:
	Camera& camera;

	std::unordered_map<unsigned int, std::unordered_map<int, TTF_Font*> > fonts;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif