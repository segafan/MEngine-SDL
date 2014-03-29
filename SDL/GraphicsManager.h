#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "FontManager.h"
#include "TextureManager.h"

class GraphicsManager : public FontManager, public TextureManager
{
public:
	GraphicsManager(SDL_Window *window, SDL_Renderer *renderer) : FontManager(window, renderer), TextureManager(window, renderer)
	{

	}
};

#endif