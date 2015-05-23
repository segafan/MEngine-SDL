#include "TextureManager.h"

TextureManager::TextureManager()
{
	
}

TextureManager::~TextureManager()
{
	Clear();
}

//Add & Destroy Textures
void TextureManager::AddTexture(Display* display, const std::string& filepath, unsigned int key)
{
	//Check if the texture exists
	if (textures.count(key) > 0)//[key] != NULL)
	{
		LOG_DEBUG("There is already a texture with this key! Key: " << key);
		//return;
	}

	//Loading Texture
	textures[key] = new Texture(display, filepath);
}
/*
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
}*/

void TextureManager::RemoveTexture(unsigned int key)
{
	textures[key]->Destroy();
	delete textures[key];
	textures[key] = NULL;
}

Texture* TextureManager::GetTexture(unsigned int key)
{
	Texture* texture = textures[key];

	if (texture == NULL || texture->IsEmpty())
	{
		LOG_ERROR("You can't get the texture because it doesn't exist! Key: " << key);

		return NULL;
	}

	return texture;
}

void TextureManager::Clear()
{
	for (auto iterator = textures.begin(); iterator != textures.end(); iterator++)
	{
		if (iterator->second != NULL)
		{
			std::cout << "Destroyed texture: " << iterator->first << std::endl;
			iterator->second->Destroy();
			delete iterator->second;
			iterator->second = NULL;
		}
	}

	textures.clear();
}