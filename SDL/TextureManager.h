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
		this->window = window;
		this->renderer = renderer;
	}
	~TextureManager()
	{
		Clear();
	}

	void AddTexture(char* filepath, char* key)
	{
		//Check if the texture exists
		if (textures[key] != NULL)
		{
			//TODO: Log this
			std::cout << "There is already a texture with this key! Key: " << key << std::endl;
			return;
		}

		//Loading Texture
		SDL_Texture* texture = NULL;
		texture = IMG_LoadTexture(renderer, filepath);
		
		//Checking if Loading was succesfull
		if (texture == NULL)
		{
			//TODO: Log this
			std::cout << "Texture couldn't be loaded! Key: " << key << " Error: " << SDL_GetError() << std::endl;
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void AddTexture(SDL_Texture* texture, char* key)
	{
		//Check if the texture exists
		if (textures[key] != NULL)
		{
			//TODO: Log this
			std::cout << "There is already a texture with this key! Key: " << key << std::endl;
			return;
		}

		//Checking if Loading was succesfull
		if (texture == NULL)
		{
			//TODO: Log this
			std::cout << "Texture couldn't be loaded! Key: " << key << " Error: " << SDL_GetError() << std::endl;
			return;
		}

		//Push to global
		textures[key] = texture;
	}
	void RemoveTexture(char* key)
	{
		if (textures[key] == NULL)
		{
			//TODO: Log this
			std::cout << "The texture can't be removed because it doesn't exist! Key:" << key << std::endl;
			return;
		}

		SDL_DestroyTexture(textures[key]);
		textures[key] = NULL;
	}
	
	SDL_Texture* GetTexture(char* key)
	{
		if (textures[key] == NULL)
		{
			//TODO: Log this
			std::cout << "You can't get the texture because it doesn't exist! Key: " << key << std::endl;
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