#include "FontManager.h"

FontManager::FontManager(Display* display) : camera(display->GetCamera())
{
	this->window = display->GetWindow();
	this->renderer = display->GetRenderer();
}

FontManager::~FontManager()
{
	Clear();
}

void FontManager::AddFont(std::string filepath, unsigned int key, int size)
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
	LOG("Font loaded " << key << " Size: " << size);
	fonts[key][size] = font;
}

void FontManager::AddFont(TTF_Font* font, unsigned int key, int size)
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

void FontManager::RemoveFont(unsigned int key, int size)
{
	if (fonts[key][size] == NULL)
	{
		LOG_DEBUG("Font couldn't be removed because it doesn't exist! Key: " << key << " Size: " << size);
		return;
	}

	TTF_CloseFont(fonts[key][size]);
	fonts[key][size] = NULL;
}

TTF_Font* FontManager::GetFont(unsigned int key, int size)
{
	if (key > fonts.size() || fonts.empty())
	{
		LOG_ERROR("You can't get the font because it doesn't exist! You are looking for a texture in unallocated memory! Key: " << key);
		return NULL;
	}
	if (fonts[key].find(size) == fonts[key].end() || fonts[key].empty())
	{
		LOG_ERROR("You can't get the font because it doesn't exist in this size! You are looking for a texture in unallocated memory! Key: " << key << " Size: " << size);
		return NULL;
	}

	TTF_Font* font = fonts[key][size];

	if (font == NULL)
	{
		LOG_ERROR("You can't get this font because it doesn't exist! Key: " << key << " Size: " << size);

		return NULL;
	}

	return font;
}

void FontManager::Clear()
{
	//Search for Font type
	for (auto iterator = fonts.begin(); iterator != fonts.end(); iterator++)
	{
		//Search for Font size
		for (auto iterator2 = iterator->second.begin(); iterator2 != iterator->second.end(); iterator2++)
		{
			//Search if the font exists
			if (iterator2->second != NULL)
			{
				//Destroy Font
				std::cout << "Destroyed font: " << iterator->first << " Size: " << iterator2->first << std::endl;
				TTF_CloseFont(iterator2->second);
				iterator2->second = NULL;
			}
		}
	}
}