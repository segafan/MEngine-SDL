//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Util.h"
#include "Rect.h"
#include "Logger.h"

#include "Camera.h"

//TOOD: This may create bugs & errors if it does redefine DrawText at the end of the file
#ifdef DrawText
#undef DrawText
#endif

#ifdef CPP11_SUPPORT
#include <unordered_map>
#else
#include <map>
#endif

enum Align
{
	ALIGN_NONE = 0,

	ALIGN_CENTER = 1,
	
	ALIGN_LEFT_X = 2,
	ALIGN_RIGHT_X = 4,
	ALIGN_CENTER_X = 8,

	ALIGN_UP_Y = 16,
	ALIGN_DOWN_Y = 32,
	ALIGN_CENTER_Y = 64
};

class FontManager
{
public:
	FontManager(Display* display, Camera& camera) : camera(camera)
	{
		this->window = display->GetWindow();
		this->renderer = display->GetRenderer();
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
			LOG_DEBUG("There is already a font with this key! Key: " << key);
			return;
		}

		TTF_Font* font = NULL;
		font = TTF_OpenFont(filepath.c_str(), size);

		if (font == NULL)
		{
			LOG_ERROR("Font couldn't be loaded! Key: " << key << " Size: " << size << " Error: " << SDL_GetError());
			return;
		}

		fonts[key][size] = font;
	}
	void AddFont(TTF_Font* font, std::string key, int size)
	{
		if (fonts[key][size] != NULL)
		{
			LOG_DEBUG("There is already a font with this key! Key: " << key);
			return;
		}

		if (font == NULL)
		{
			LOG_ERROR("Font couldn't be added, because it's NULL! Key: " << key << " Size: " << size << " Error: " << SDL_GetError());
			return;
		}

		fonts[key][size] = font;
	}
	void RemoveFont(std::string key, int size)
	{
		if (fonts[key][size] == NULL)
		{
			LOG_DEBUG("Font couldn't be removed because it doesn't exist! Key: " << key << " Size: " << size);
			return;
		}

		TTF_CloseFont(fonts[key][size]);
		fonts[key][size] = NULL;
	}

	TTF_Font* GetFont(std::string key, int size)
	{
		TTF_Font* font = fonts[key][size];

		if (font == NULL)
		{
			if (errorShown[key][size] == 0 || errorShown[key][size] == false)
			{
				LOG_ERROR("You can't get this font because it doesn't exist! Key: " << key << " Size: " << size);
				errorShown[key][size] = true;
			}

			return NULL;
		}

		return font;
	}

	void Clear()
	{
#ifdef CPP11_SUPPORT
		typedef std::unordered_map<std::string, std::unordered_map<int, TTF_Font*> >::iterator it_type;

		typedef std::unordered_map<int, TTF_Font*>::iterator it_type2;
#else
		typedef std::map<std::string, std::map<int, TTF_Font*> >::iterator it_type;

		typedef std::map<int, TTF_Font*>::iterator it_type2;
#endif
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
					fonts[iterator->first][iterator2->first] = NULL;
				}
			}
		}
	}

	//Draw Font
	//TODO: Add more Draw() options
	//TODO: Add every letter as a Texture and draw every letter of the text one by one
	//TDOD: Add align Center | Left |Right

	//Drawing with SDL_Rect

	void DrawText(std::string key, int size, std::string text, SDL_Rect *pos, SDL_Color color, int align)
	{
		if (text == "")
			return;

		if (GetFont(key, size) == NULL)
			return;

		//Create Text Surface
		SDL_Surface* surface = NULL;
		surface = TTF_RenderText_Solid(fonts[key][size], text.c_str(), color);

		if (surface == NULL)
		{
			LOG_ERROR("Couldn't create surface from Font! Key: " << key << " Size: " << size << " Text: " << text << " Error: " << TTF_GetError());
			return;
		}

		//Create Texture from Surface
		SDL_Texture* texture = NULL;
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL)
		{
			LOG_ERROR("Couldn't create texture from surface(made from Font)! Key: " << key << " Size: " << size << " Text: " << text << " Error: " << SDL_GetError());
			return;
		}

		//Free Surface
		SDL_FreeSurface(surface);

		//Query Texture for w and h
		if (SDL_QueryTexture(texture, NULL, NULL, &pos->w, &pos->h) == -1)
		{
			LOG_ERROR("Couldn't query texture made from surface(made from Font)! Key: " << key << " Size: " << size << " Text: " << text << " Error: " << SDL_GetError());
			return;
		}

		//Align
		
		SDL_Rect tempPos = *(Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect();

		//Recalculate coordinates
		if (ContainsFlag(align, ALIGN_CENTER))
		{
			tempPos.x = tempPos.x - (tempPos.w / 2);
			tempPos.y = tempPos.y - (tempPos.h / 2);
		}

		if (ContainsFlag(align, ALIGN_CENTER_X))
			tempPos.x = tempPos.x - (tempPos.w / 2);
		if (ContainsFlag(align, ALIGN_CENTER_Y))
			tempPos.y = tempPos.y - (tempPos.h / 2);

		if (ContainsFlag(align, ALIGN_RIGHT_X))
			tempPos.x = tempPos.x - tempPos.w;

		if (ContainsFlag(align, ALIGN_DOWN_Y))
			tempPos.y = tempPos.y - tempPos.h;

		SDL_RenderCopy(renderer, texture, NULL, &tempPos);

		//Destroy Texture
		SDL_DestroyTexture(texture);
	}
	void DrawText(std::string key, int size, std::string text, SDL_Rect *pos, Color color, int align)
	{
		DrawText(key, size, text, pos, color.ToSDLColor(), align);
	}

	//Drawing with own Rect

	void DrawText(std::string key, int size, std::string text, Rect *pos, SDL_Color color, int align)
	{
		DrawText(key, size, text, pos->ToSDLRect(), color, align);
	}
	void DrawText(std::string key, int size, std::string text, Rect *pos, Color color, int align)
	{
		DrawText(key, size, text, pos->ToSDLRect(), color.ToSDLColor(), align);
	}
private:
	Camera& camera;

#ifdef CPP11_SUPPORT
	std::unordered_map<std::string, std::unordered_map<int, TTF_Font*> > fonts;

	std::unordered_map<std::string, std::unordered_map<int, bool> > errorShown;
#else
	std::map<std::string, std::map<int, TTF_Font*> > fonts;

	std::map<std::string, std::map<int, bool> > errorShown;
#endif

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif