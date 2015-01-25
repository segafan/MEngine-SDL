//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Rect.h"
#include "Logger.h"
#include "Display.h"
#include "Camera.h"

#ifdef CPP11_SUPPORT
#include <unordered_map>
#else
#include <map>
#endif

#ifndef MAX_TEXTURE_NUM
#define MAX_TEXTURE_NUM 100
#endif

class TextureManager
{
public:
	TextureManager(Display* display);
	~TextureManager();

	//Add & Destroy Textures
	void AddTexture(const std::string& filepath, unsigned int key);
	void AddTexture(SDL_Texture* texture, unsigned int  key);
	void RemoveTexture(unsigned int key);

	SDL_Texture* GetTexture(unsigned int key);

	void Clear();

	//Draw Textures
	//TODO: Add more options to Draw

	//Drawing using SDL_Rect
	void DrawTexture(unsigned int key, SDL_Rect *pos);
	void DrawTexture(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos);

	void DrawTextureRotated(unsigned int key, SDL_Rect *pos, double angle);
	void DrawTextureRotated(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos, double angle);

	void DrawTextureFlip(unsigned int key, SDL_Rect *pos, SDL_RendererFlip flip);
	void DrawTextureFlip(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip);

	//Drawing using own Rect class

	void DrawTexture(unsigned int key, Rect *pos);
	void DrawTexture(unsigned int key, Rect *srcpos, Rect *pos);

	void DrawTextureRotated(unsigned int key, Rect *pos, double angle);
	void DrawTextureRotated(unsigned int key, Rect *srcpos, Rect *pos, double angle);

	void DrawTextureFlip(unsigned int key, Rect *pos, SDL_RendererFlip flip);
	void DrawTextureFlip(unsigned int key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip);
private:
	Camera& camera;

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::vector<SDL_Texture*> textures;
	std::vector<bool> errorShown;
};

#endif