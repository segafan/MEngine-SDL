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

class TextureManager
{
public:
	TextureManager(Display* display);
	~TextureManager();

	//Add & Destroy Textures
	void AddTexture(const std::string& filepath, std::string key);
	void AddTexture(SDL_Texture* texture, std::string  key);
	void RemoveTexture(std::string key);

	SDL_Texture* GetTexture(std::string key);

	void Clear();

	//Draw Textures
	//TODO: Add more options to Draw

	//Drawing using SDL_Rect
	void DrawTexture(std::string key, SDL_Rect *pos);
	void DrawTexture(std::string key, SDL_Rect *srcpos, SDL_Rect *pos);

	void DrawTextureRotated(std::string key, SDL_Rect *pos, double angle);
	void DrawTextureRotated(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, double angle);

	void DrawTextureFlip(std::string key, SDL_Rect *pos, SDL_RendererFlip flip);
	void DrawTextureFlip(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip);

	//Drawing using own Rect class

	void DrawTexture(std::string key, Rect *pos);
	void DrawTexture(std::string key, Rect *srcpos, Rect *pos);

	void DrawTextureRotated(std::string key, Rect *pos, double angle);
	void DrawTextureRotated(std::string key, Rect *srcpos, Rect *pos, double angle);

	void DrawTextureFlip(std::string key, Rect *pos, SDL_RendererFlip flip);
	void DrawTextureFlip(std::string key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip);
private:
	Camera& camera;

	SDL_Window* window;
	SDL_Renderer* renderer;

#ifdef CPP11_SUPPORT
	std::unordered_map<std::string, SDL_Texture*> textures;

	std::unordered_map<std::string, bool> errorShown;
#else
	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, bool> errorShown;
#endif
};

#endif