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

	void SetAlphaMod(int alpha);
	void SetColorMod(Color color);

	int GetAlphaMod();
	Color GetColorMod();

private:
	SDL_Texture* m_texture;
};

#endif