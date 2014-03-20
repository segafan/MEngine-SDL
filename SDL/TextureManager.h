#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <vector>
#include <cstring>

#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
	TextureManager(SDL_Window* window, SDL_Renderer* renderer)
	{
		this->renderer = renderer;
	}
	~TextureManager()
	{
		Clear();
	}

	void AddTexture(char* filepath, char* key)
	{
		//Loading Texture
		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(renderer, filepath);
		
		//Checking if Loading was succesfull
		if (texture == NULL)
		{
			//TODO: Log this
			std::cout << "Texture couldn't be loaded! Key: " << key << SDL_GetError() << std::endl;
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void RemoveTexture(char* key)
	{
		SDL_DestroyTexture(textures[key]);
		textures[key] = NULL;
	}
	
	SDL_Texture* GetTexture(char* key)
	{
		return textures[key];
	}

	void Clear()
	{
		typedef std::map<std::string, SDL_Texture*>::iterator it_type;

		for (it_type iterator = textures.begin(); iterator != textures.end(); iterator++)
		{
			std::cout << "Destroyed texture: " << iterator->first << std::endl;
			SDL_DestroyTexture(textures[iterator->first]);
		}
		
		textures.clear();
	}

	SDL_Window* GetWindow()
	{
		return window;
	}

	SDL_Renderer* GetRenderer()
	{
		return renderer;
	}
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::map<std::string, SDL_Texture*> textures;
};

#endif