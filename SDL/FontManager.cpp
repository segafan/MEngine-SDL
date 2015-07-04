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

void FontManager::AddFont(std::string filepath, std::string key, int size)
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

void FontManager::AddFont(TTF_Font* font, std::string key, int size)
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

void FontManager::RemoveFont(std::string key, int size)
{
	if (fonts[key][size] == NULL)
	{
		LOG_DEBUG("Font couldn't be removed because it doesn't exist! Key: " << key << " Size: " << size);
		return;
	}

	TTF_CloseFont(fonts[key][size]);
	fonts[key][size] = NULL;
}

TTF_Font* FontManager::GetFont(std::string key, int size)
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

void FontManager::DrawText(std::string key, int size, std::string text, SDL_Rect *pos, SDL_Color color, int align)
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

void FontManager::DrawText(std::string key, int size, std::string text, SDL_Rect *pos, Color color, int align)
{
	DrawText(key, size, text, pos, color.ToSDLColor(), align);
}

void FontManager::DrawText(std::string key, int size, std::string text, Rect *pos, SDL_Color color, int align)
{
	DrawText(key, size, text, pos->ToSDLRect(), color, align);
}

void FontManager::DrawText(std::string key, int size, std::string text, Rect *pos, Color color, int align)
{
	DrawText(key, size, text, pos->ToSDLRect(), color.ToSDLColor(), align);
}
