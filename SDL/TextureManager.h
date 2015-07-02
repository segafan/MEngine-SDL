//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Rect.h"
#include "Logger.h"
#include "Display.h"
#include "Camera.h"
#include "Texture.h"

#ifdef CPP11_SUPPORT
#include <unordered_map>
#else
#include <map>
#endif

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	//Add & Destroy Textures
	void AddTexture(Display* display, const std::string& filepath, unsigned int key);
	//void AddTexture(SDL_Texture* texture, unsigned int  key);
	void RemoveTexture(unsigned int key);

	Texture* GetTexture(unsigned int key);

	void Clear();

private:
	std::unordered_map<unsigned int, Texture*> textures;
};

#endif