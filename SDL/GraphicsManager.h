//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include "FontManager.h"
#include "TextureManager.h"

class GraphicsManager : public FontManager, public TextureManager
{
public:
	GraphicsManager(Display* display);

	//TODO: Clean up
	void AddGraphicScript(const std::string& filepath);

private:
	std::string imageBasepath;
	std::string fontBasepath;
	std::string animationBasepath;
};

#endif