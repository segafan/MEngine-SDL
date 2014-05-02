#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <map>
#include <cstring>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Rect.h"
#include "Logger.h"

//TOOD: This may create bugs & errors if it does redefine DrawText at the end of the file
#ifdef DrawText
#undef DrawText
#endif

enum Align
{
	ALIGN_LEFT = 0,
	ALIGN_RIGHT = 1,
	ALIGN_CENTER = 2
};

class FontManager
{
public:
	FontManager(SDL_Window *window, SDL_Renderer *renderer, Logger *logger)
	{
		this->logger = logger;
		this->window = window;
		this->renderer = renderer;
	}
	~FontManager()
	{
		Clear();
	}

	//Add & Destroy Fonts
	void AddFont(std::string filepath, std::string key, int size)
	{
		if (fonts[key][size] != NULL)
		{
			logger->LogLine("There is already a font with this key! Key: ", key);
			return;
		}

		TTF_Font* font = NULL;
		font = TTF_OpenFont(filepath.c_str(), size);

		if (font == NULL)
		{
			logger->LogLine("Font couldn't be loaded! Key: ", key, " Size: ", NumberToString(size), " Error: ", SDL_GetError());
			return;
		}

		fonts[key][size] = font;
	}
	void RemoveFont(std::string key, int size)
	{
		if (fonts[key][size] == NULL)
		{
			logger->LogLine("Font couldn't be removed because it doesn't exist! Key: ", key, " Size: ", NumberToString(size));
			return;
		}

		TTF_CloseFont(fonts[key][size]);
		fonts[key][size] = NULL;
	}

	TTF_Font* GetFont(std::string key, int size)
	{
		if (fonts[key][size] == NULL)
		{
			if (errorShown[key][size] == 0 || errorShown[key][size] == false)
			{
				logger->LogLine("You can't get this font because it doesn't exist! Key: ", key, " Size: ", NumberToString(size));
				errorShown[key][size] = true;
			}

			return NULL;
		}

		return fonts[key][size];
	}

	void Clear()
	{
		typedef std::map<std::string, std::map<int, TTF_Font*> >::iterator it_type;

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
					std::cout << "Destroyed font: " << iterator->first << " Size: " << iterator2->first << std::endl;
					TTF_CloseFont(fonts[iterator->first][iterator2->first]);
				}
			}
		}
	}

	//Draw Font
	//TODO: Add more Draw() options
	//TODO: Add every letter as a Texture and draw every letter of the text one by one
	//TDOD: Add align Center | Left |Right

	//Drawing with SDL_Rect

	void DrawText(std::string key, std::string text, int size, SDL_Rect *pos, SDL_Color color)
	{
		if (fonts[key][size] == NULL)
		{
			logger->LogLine("The text can't be drawn beacuse the font doesn't exist! Key: ", key, " Size: ", NumberToString(size));
			return;
		}

		//Create Text Surface
		SDL_Surface* surface = NULL;
		surface = TTF_RenderText_Solid(fonts[key][size], text.c_str(), color);

		if (surface == NULL)
		{
			logger->LogLine("Couldn't create surface from Font! Key: ", key, " Size: ", NumberToString(size), " Text: ", text);
			return;
		}

		//Create Texture from Surface
		SDL_Texture* texture = NULL;
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL)
		{
			logger->LogLine("Couldn't create texture from surface(made from Font)! Key: ", key, " Size: ", NumberToString(size), " Text: ", text);
			return;
		}

		//Free Surface
		SDL_FreeSurface(surface);

		//Query Texture for w and h
		if (SDL_QueryTexture(texture, NULL, NULL, &pos->w, &pos->h) == -1)
		{
			logger->LogLine("Couldn't query texture from surface(made from Font)! Key: ", key, " Size: ", NumberToString(size), " Text: ", text);
			return;
		}

		//Render
		SDL_RenderCopy(renderer, texture, NULL, pos);

		//Destroy Texture
		SDL_DestroyTexture(texture);
	}

	//Drawing with own Rect

	void DrawText(std::string key, std::string text, int size, Rect *pos, SDL_Color color)
	{
		DrawText(key, text, size, pos->GetSDLRect(), color);
	}
private:
	std::map<std::string, std::map<int, TTF_Font*> > fonts;

	std::map<std::string, std::map<int, bool> > errorShown;

	Logger *logger;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif