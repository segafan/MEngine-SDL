#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include "Display.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
public:

	Texture();
	Texture(Display* display, const std::string& filepath);

	~Texture();

	void Load(Display* display, const std::string& filepath);

	void Destroy();

	bool IsEmpty();

	SDL_Texture* GetTexture();

	void SetAlpha(int alpha);
	int GetAlpha();

private:
	SDL_Texture* m_texture;
};

#endif