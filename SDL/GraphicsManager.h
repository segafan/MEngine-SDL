#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "FontManager.h"
#include "TextureManager.h"

class GraphicsManager : public FontManager, public TextureManager
{
public:
	GraphicsManager(SDL_Window *window, SDL_Renderer *renderer, Logger *logger) : FontManager(window, renderer, logger), TextureManager(window, renderer, logger)
	{

	}
};

#endif