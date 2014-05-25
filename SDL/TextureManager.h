#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "Rect.h"
#include "Logger.h"

class TextureManager
{
public:
	TextureManager(SDL_Window* window, SDL_Renderer* renderer, Logger *logger)
	{
		this->logger = logger;

		this->window = window;
		this->renderer = renderer;
	}
	~TextureManager()
	{
		Clear();
	}

	//Add & Destroy Textures
	void AddTexture(std::string filepath, std::string key)
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
		}

		//Push to global
		textures[key] = texture;
	}
	void AddTexture(SDL_Texture* texture, std::string key)
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
			logger->LogLine("Texture couldn't be loaded! Key: ", key, " Error: ", SDL_GetError());
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void RemoveTexture(std::string key)
	{
		if (textures[key] == NULL)
		{
			logger->LogLine("The texture can't be removed because it doesn't exist! Key:", key);
			return;
		}

		SDL_DestroyTexture(textures[key]);
		textures[key] = NULL;
	}
	
	SDL_Texture* GetTexture(std::string key)
	{
		if (textures[key] == NULL)
		{
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
		typedef std::map<std::string, SDL_Texture*>::iterator it_type;

		for (it_type iterator = textures.begin(); iterator != textures.end(); iterator++)
		{
			if (textures[iterator->first] != NULL)
			{
				std::cout << "Destroyed texture: " << iterator->first << std::endl;
				SDL_DestroyTexture(textures[iterator->first]);
			}
		}
		
		textures.clear();
	}

	//Draw Textures
	//TODO: Add more options to Draw

	//Drawing using SDL_Rect
	void DrawTexture(std::string key, SDL_Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), NULL, pos);
	}
	void DrawTexture(std::string key, SDL_Rect *srcpos, SDL_Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), srcpos, pos);
	}

	void DrawTextureRotated(std::string key, SDL_Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, pos, angle, NULL, SDL_FLIP_NONE);
	}
	void DrawTextureRotated(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, pos, angle, NULL, SDL_FLIP_NONE);
	}

	void DrawTextureFlip(std::string key, SDL_Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, pos, 0, NULL, flip);
	}
	void DrawTextureFlip(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, pos, 0, NULL, flip);
	}

	//Drawing using own Rect class

	void DrawTexture(std::string key, Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), NULL, pos->ToSDLRect());
	}
	void DrawTexture(std::string key, Rect *srcpos, Rect *pos)
	{
		SDL_RenderCopy(renderer, GetTexture(key), srcpos->ToSDLRect(), pos->ToSDLRect());
	}

	void DrawTextureRotated(std::string key, Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, pos->ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}
	void DrawTextureRotated(std::string key, Rect *srcpos, Rect *pos, double angle)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), pos->ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
	}

	void DrawTextureFlip(std::string key, Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), NULL, pos->ToSDLRect(), 0, NULL, flip);
	}
	void DrawTextureFlip(std::string key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), pos->ToSDLRect(), 0, NULL, flip);
	}
private:
	Logger *logger;

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Texture*> textures;

	std::map<std::string, bool> errorShown;
};

#endif