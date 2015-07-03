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

#include <vector>

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
	void Reserve(int num);

private:
	std::vector<Texture*> textures;
};

#endif