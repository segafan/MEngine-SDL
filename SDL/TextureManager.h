//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Rect.h"
#include "Logger.h"

#include "Camera.h"

class TextureManager
{
public:
	TextureManager(Display* display, Camera& camera, Logger *logger) : camera(camera)
	{
		textures.reserve(maxSize);
		errorShown.reserve(maxSize);

		for (int i = 0; i < maxSize; i++)
		{
			textures.push_back(NULL);
			errorShown.push_back(false);
		}

		this->logger = logger;

		this->window = display->GetWindow();
		this->renderer = display->GetRenderer();
	}
	~TextureManager()
	{
		Clear();
	}

	//Add & Destroy Textures
	void AddTexture(const std::string& filepath, const int& key)
	{
		//Check if the texture exists
		if (textures[key] != NULL)
		{
			logger->LogLine("There is already a texture with this key! Key: ", key);
			return;
		}

		//Loading Texture
		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(renderer, filepath.c_str());
		
		//Checking if Loading was succesfull
		if (texture == NULL)
		{
			logger->LogLine("Texture couldn't be loaded! Key: ", key, " Error: ", SDL_GetError());
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void AddTexture(SDL_Texture* texture, const int& key)
	{
		//Check if the texture exists
		if (textures[key] != NULL)
		{
			logger->LogLine("There is already a texture with this key! Key: ", key);
			return;
		}

		//Checking if Loading was succesfull
		if (texture == NULL)
		{
			logger->LogLine("Texture doesn't exist! Key: ", key, " Error: ", SDL_GetError());
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void RemoveTexture(const int& key)
	{
		if (textures[key] == NULL)
		{
			logger->LogLine("The texture can't be removed because it doesn't exist! Key:", key);
			return;
		}

		SDL_DestroyTexture(textures[key]);
		textures[key] = NULL;
		errorShown[key] = false;
	}

	SDL_Texture* GetTexture(const int& key)
	{
		if (textures[key] == NULL)
		{
			//TODO: May not work on Linux (the if statment)
			if (errorShown[key] == 0 || errorShown[key] == false)
			{
				logger->LogLine("You can't get the texture because it doesn't exist! Key: ", key);
				errorShown[key] = true;
			}

			return NULL;
		}

		return textures[key];
	}

	void Clear()
	{
		for (int i = 0; i < textures.size(); i++)
		{
			if (textures[i] != NULL)
			{
				std::cout << "Destroyed texture: " << i << std::endl;
				SDL_DestroyTexture(textures[i]);
				textures[i] = NULL;
			}
		}
		
		textures.clear();
	}

	//Draw Textures
	//TODO: Add more options to Draw

	//Drawing using SDL_Rect
	void DrawTexture(const int& key, SDL_Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
	}
	void DrawTexture(const int& key, SDL_Rect *srcpos, SDL_Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
	}

	void DrawTextureRotated(const int& key, SDL_Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}
	void DrawTextureRotated(const int& key, SDL_Rect *srcpos, SDL_Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}

	void DrawTextureFlip(const int& key, SDL_Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
	}
	void DrawTextureFlip(const int& key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
	}

	//Drawing using own Rect class

	void DrawTexture(const int& key, Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect());
	}
	void DrawTexture(const int& key, Rect *srcpos, Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect());
	}

	void DrawTextureRotated(const int& key, Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}
	void DrawTextureRotated(const int& key, Rect *srcpos, Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}

	void DrawTextureFlip(const int& key, Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
	}
	void DrawTextureFlip(const int& key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
	}
private:
	Camera& camera;
	Logger *logger;

	SDL_Window* window;
	SDL_Renderer* renderer;

	const int maxSize = 255;

	std::vector<SDL_Texture*> textures;

	std::vector<bool> errorShown;
};

#endif