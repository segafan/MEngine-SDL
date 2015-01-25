#include "TextureManager.h"

TextureManager::TextureManager(Display* display) : camera(display->GetCamera())
{
	this->window = display->GetWindow();
	this->renderer = display->GetRenderer();

	for (int i = 0; i < MAX_TEXTURE_NUM; i++)
	{
		textures.push_back(NULL);
		errorShown.push_back(false);
	}
}
TextureManager::~TextureManager()
{
	Clear();
}

//Add & Destroy Textures
void TextureManager::AddTexture(const std::string& filepath, unsigned int key)
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

	//Checking if Loading was successful
	if (texture == NULL)
	{
		LOG_ERROR("Texture couldn't be loaded! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	//Push to global
	textures[key] = texture;
}
void TextureManager::AddTexture(SDL_Texture* texture, unsigned int key)
{
	//Check if the texture exists
	if (textures[key] != NULL)
	{
		LOG_DEBUG("There is already a texture with this key! Key: " << key);
		return;
	}

	//Checking if Loading was successfully
	if (texture == NULL)
	{
		LOG_ERROR("Texture couldn't be added! It's NULL! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	//Push to global
	textures[key] = texture;
}

void TextureManager::RemoveTexture(unsigned int key)
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

SDL_Texture* TextureManager::GetTexture(unsigned int key)
{
	SDL_Texture* texture = textures[key];

	if (texture == NULL)
	{
		//TODO: May not work on Linux (the if statement)
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
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		if (textures[i] != NULL)
		{
			std::cout << "Destroyed texture: " << i << std::endl;
			SDL_DestroyTexture(textures[i]);
			textures[i] = NULL;
		}
	}

	textures.clear();
}

//Draw Textures
//TODO: Add more options to Draw

//Drawing using SDL_Rect
void TextureManager::DrawTexture(unsigned int key, SDL_Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
}
void TextureManager::DrawTexture(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect());
}

void TextureManager::DrawTextureRotated(unsigned int key, SDL_Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}
void TextureManager::DrawTextureRotated(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTextureFlip(unsigned int key, SDL_Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}
void TextureManager::DrawTextureFlip(unsigned int key, SDL_Rect *srcpos, SDL_Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos, (Rect(pos->x, pos->y, pos->w, pos->h) - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}

//Drawing using own Rect class

void TextureManager::DrawTexture(unsigned int key, Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect());
}
void TextureManager::DrawTexture(unsigned int key, Rect *srcpos, Rect *pos)
{
	SDL_RenderCopy(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect());
}

void TextureManager::DrawTextureRotated(unsigned int key, Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}
void TextureManager::DrawTextureRotated(unsigned int key, Rect *srcpos, Rect *pos, double angle)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void TextureManager::DrawTextureFlip(unsigned int key, Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), NULL, (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}
void TextureManager::DrawTextureFlip(unsigned int key, Rect *srcpos, Rect *pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, GetTexture(key), srcpos->ToSDLRect(), (*pos - camera.GetView()).ToSDLRect(), 0, NULL, flip);
}