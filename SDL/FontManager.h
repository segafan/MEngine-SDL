#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <map>
#include <cstring>

#include <SDL.h>
#include <SDL_ttf.h>

class FontManager
{
public:
	FontManager(SDL_Window *window, SDL_Renderer *renderer)
	{
		this->window = window;
		this->renderer = renderer;
	}
	~FontManager()
	{
		Clear();
	}

	//Add & Destroy Fonts
	void AddFont(char* filepath, char* key, int size)
	{
		if (fonts[key][size] != NULL)
		{
			//TODO: Log this
			std::cout << "There is already a font with this key! Key: " << key << std::endl;
			return;
		}

		TTF_Font* font = NULL;
		font = TTF_OpenFont(filepath, size);

		if (font == NULL)
		{
			//TODO: Log this
			std::cout << "Font couldn't be loaded! Key: " << key << " Error: " << SDL_GetError() << std::endl;
			return;
		}

		fonts[key][size] = font;
	}
	void RemoveFont(char* key, int size)
	{
		if (fonts[key][size] == NULL)
		{
			//TODO: Log this
			std::cout << "Font couldn't be removed because it doesn't exist! Key: " << key << std::endl;
			return;
		}

		TTF_CloseFont(fonts[key][size]);
		fonts[key][size] = NULL;
	}

	TTF_Font* GetFont(char* key, int size)
	{
		if (fonts[key][size] == NULL)
		{
			//TODO: Log this
			std::cout << "You can't get this font because it doesn't exist! Key: " << key << std::endl;
			return NULL;
		}

		return fonts[key][size];
	}

	void Clear()
	{
		typedef std::map<std::string, std::map<int, TTF_Font*>>::iterator it_type;

		typedef std::map<int, TTF_Font*>::iterator it_type2;

		//Search for Font type
		for (it_type iterator = fonts.begin(); iterator != fonts.end(); iterator++)
		{
			//Search for Font size
			for (it_type2 iterator2 = iterator->second.begin(); iterator2 != iterator->second.end(); iterator2++)
			{
				//Search if the sont exists
				if (fonts[iterator->first][iterator2->first] != NULL)
				{
					//Destroy Font
					std::cout << "Destroyed texture: " << iterator->first << " Size: " << iterator2->first << std::endl;
					TTF_CloseFont(fonts[iterator->first][iterator2->first]);
				}
			}
		}
	}

	//Draw Font
	//TODO: Add more Draw() options
	//TODO: Add every letter as a Texture and draw every letter of the text one by one
	void DrawText(char* text, char* key, int size)
	{
		SDL_Color color = { 0, 0, 0 };
		
		SDL_Surface* surface = NULL;
		surface = TTF_RenderText_Solid(fonts[key][size], text, color);

		SDL_Texture* texture = NULL;
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);

		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_DestroyTexture(texture);
	}

private:
	std::map<std::string,std::map<int, TTF_Font*>> fonts;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif