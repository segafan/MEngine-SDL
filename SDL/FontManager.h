#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL_ttf.h>

#include <cstring>

#include <map>

class FontManager
{
public:
	FontManager()
	{
		
	}
	~FontManager()
	{
		Clear();
	}

	void AddFont(char* filepath, char* key, int size)
	{
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
		TTF_CloseFont(fonts[key][size]);
		fonts[key][size] = NULL;
	}

	TTF_Font* GetFont(char* key, int size)
	{
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

private:
	std::map<std::string,std::map<int, TTF_Font*>> fonts;
};

#endif