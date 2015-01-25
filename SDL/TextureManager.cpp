#include "TextureManager.h"

TextureManager::TextureManager(Display* display) : camera(display->GetCamera())
{
	this->window = display->GetWindow();
	this->renderer = display->GetRenderer();
}
TextureManager::~TextureManager()
{
	Clear();
}

//Add & Destroy Textures
void TextureManager::AddTexture(const std::string& filepath, std::string key)
{
	//Check if the texture exists
	if (textures[key] != NULL)
	{
		LOG_DEBUG("There is already a texture with this key! Key: " << key);
		return;
	}

	//Loading Texture
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filepath.c_str());

	//Checking if Loading was succesfull
	if (texture == NULL)
	{
		LOG_ERROR("Texture couldn't be loaded! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	//Push to global
	textures[key] = texture;
}
void TextureManager::AddTexture(SDL_Texture* texture, std::string  key)
{
	//Check if the texture exists
	if (textures[key] != NULL)
	{
		LOG_DEBUG("There is already a texture with this key! Key: " << key);
		return;
	}

	//Checking if Loading was succesfull
	if (texture == NULL)
	{
		LOG_ERROR("Texture couldn't be added! It's NULL! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	//Push to global
	textures[key] = texture;
}

void TextureManager::RemoveTexture(std::string key)
{
	if (textures[key] == NULL)
	{
		LOG_DEBUG("The texture can't be removed because it doesn't exist! Key: " << key);
		return;
	}

	SDL_DestroyTexture(textures[key]);
	textures[key] = NULL;
	errorShown[key] = false;
}

SDL_Texture* TextureManager::GetTexture(std::string key)
{
	SDL_Texture* texture = textures[key];

	if (texture == NULL)
	{
		//TODO: May not work on Linux (the if statment)
		if (errorShown[key] == 0 || errorShown[key] == false)
		{
			LOG_ERROR("You can't get the texture because it doesn't exist! Key: " << key);
			errorShown[key] = true;
		}

		return NULL;
	}

	return texture;
}

void TextureManager::Clear()
{
#ifdef CPP11_SUPPORT
	typedef std::unordered_map<std::string, SDL_Texture*>::iterator it_type;
#else
	typedef std::map<std::string, SDL_Texture*>::iterator it_type;
#endif
	for (it_type iterator = textures.begin(); iterator != textures.end(); iterator++)
	{
		if (textures[iterator->first] != NULL)
		{
			std::cout << "Destroyed texture: " << iterator->first << std::endl;
			SDL_DestroyTexture(textures[iterator->first]);
			textures[iterator->first] = NULL;
		}
	}

	textures.clear();
}

//Draw Textures
//TODO: Add more options to Draw

//Drawing using SDL_Rect
void TextureManager::DrawTexture(std::string key, SDL_Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
}
void TextureManager::DrawTexture(std::string key, SDL_Rect *srcpos, SDL_Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
}

void TextureManager::DrawTextureRotated(std::string key, SDL_Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}
void TextureManager::DrawTextureRotated(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTextureFlip(std::string key, SDL_Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}
void TextureManager::DrawTextureFlip(std::string key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}

//Drawing using own Rect class

void TextureManager::DrawTexture(std::string key, Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect());
}
void TextureManager::DrawTexture(std::string key, Rect *srcpos, Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect());
}

void TextureManager::DrawTextureRotated(std::string key, Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}
void TextureManager::DrawTextureRotated(std::string key, Rect *srcpos, Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTextureFlip(std::string key, Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}
void TextureManager::DrawTextureFlip(std::string key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}