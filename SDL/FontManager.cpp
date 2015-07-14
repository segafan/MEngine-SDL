#include "FontManager.h"

FontManager::FontManager()
{
	
}

FontManager::~FontManager()
{
	Clear();
}

void FontManager::AddFont(Display* display, std::string filepath, unsigned int key, unsigned int size)
{
	AddFont(display, filepath, key, size, ASCII_EXTENDED);
}

void FontManager::AddFont(Display* display, std::string filepath, unsigned int key, unsigned int size, unsigned int numchar)
{
	if (key > (fonts.size() - 1) || fonts.empty())
	{
		if (key == fonts.size())
		{
			LOG_DEBUG("No more allocated memory for textures! Allocating +1 ...");
			fonts.push_back(NULL);
		}
		else
		{
			LOG_ERROR("No more allocated memory for textures! Allocating " << key - (fonts.size() - 1) << " more...");
			for (unsigned int i = fonts.size(); i <= key; i++)
				fonts.push_back(NULL);
		}
	}
	if (fonts[key] != NULL)
	{
		LOG_DEBUG("There is already a font with this key! Key: " << key);
		return;
	}

	fonts[key] = new Font(display, filepath, size, numchar);
}

void FontManager::RemoveFont(unsigned int key)
{
	if (fonts[key] != NULL)
	{
		std::cout << "Destroyed font: " << key << std::endl;
		fonts[key]->Destroy();
		delete fonts[key];
		fonts[key] = NULL;
	}
}

Font* FontManager::GetFont(unsigned int key)
{
	if (key > fonts.size() || fonts.empty())
	{
		LOG_ERROR("You can't get the texture because it doesn't exist! You are looking for a texture in unallocated memory! Key: " << key);
		return NULL;
	}

	Font* font = fonts[key];

	if (font == NULL)
	{
		LOG_ERROR("You can't get the texture because it doesn't exist! Key: " << key);
		return NULL;
	}
	if (font->IsEmpty())
	{
		LOG_ERROR("You can't get the texture because it's empty exist! Key: " << key);
		return NULL;
	}

	return font;
}

void FontManager::Clear()
{
	for (unsigned int i = 0; i < fonts.size(); i++)
	{
		if (fonts[i] != NULL)
		{
			std::cout << "Destroyed font: " << i << std::endl;
			fonts[i]->Destroy();
			delete fonts[i];
			fonts[i] = NULL;
		}
	}
}