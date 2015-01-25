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
	Texture(SDL_Renderer* renderer, const std::string& filepath);
	Texture(Display* display, const std::string& filepath);

	~Texture();

	void Load(SDL_Renderer* renderer, const std::string& filepath);
	void Load(Display* display, const std::string& filepath);

	void Destroy();

	void Draw(Display* display, Rect* pos);
	void Draw(Display* display, Rect* src, Rect* pos);

	void DrawRotated(Display* display, Rect* pos, float angle);
	void DrawRotated(Display* display, Rect* src, Rect* pos, float angle);

	void DrawFlipped(Display* display, Rect* pos, SDL_RendererFlip flip);
	void DrawFlipped(Display* display, Rect* src, Rect* pos, SDL_RendererFlip flip);

private:
	SDL_Texture* m_texture;
};

#endif