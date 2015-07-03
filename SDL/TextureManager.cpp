#include "TextureManager.h"

TextureManager::TextureManager()
{
	//Reserve(100);
}

TextureManager::~TextureManager()
{
	Clear();
}

//Add & Destroy Textures
void TextureManager::AddTexture(Display* display, const std::string& filepath, unsigned int key)
{
	if (key > (textures.size() - 1))
	{
		if (key == textures.size())
		{
			LOG_DEBUG("No more allocated memory for textures! Allocating +1 ...");
			textures.push_back(NULL);
		}
		else
		{
			LOG_ERROR("No more allocated memory for textures! Allocating " << key - (textures.size() - 1) << " more...");
			for (int i = textures.size(); i <= key; i++)
				textures.push_back(NULL);
		}
	}
	//Check if the texture exists
	if (textures[key] != NULL)
	{
		LOG_DEBUG("There is already a texture with this key! Key: " << key);
		//return;
	}

	//Loading Texture
	textures[key] = new Texture(display, filepath);
}

void TextureManager::RemoveTexture(unsigned int key)
{
	textures[key]->Destroy();
	delete textures[key];
	textures[key] = NULL;
}

Texture* TextureManager::GetTexture(unsigned int key)
{
	if (key > textures.size())
	{
		LOG_ERROR("You can't get the texture because it doesn't exist! You are looking ofr a texture in unallocated memory! Key: " << key);
		return NULL;
	}

	Texture* texture = textures[key];

	if (texture == NULL)
	{
		LOG_ERROR("You can't get the texture because it doesn't exist! Key: " << key);
		return NULL;
	}
	if (texture->IsEmpty())
	{
		LOG_ERROR("You can't get the texture because it's empty exist! Key: " << key);
		return NULL;
	}

	return texture;
}

void TextureManager::Clear()
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i] != NULL)
		{
			std::cout << "Destroyed texture: " << i << std::endl;
			textures[i]->Destroy();
			delete textures[i];
			textures[i] = NULL;
		}
	}

	textures.clear();
}

void TextureManager::Reserve(int num)
{
	for (int i = textures.size(); i < num; i++)
	{
		textures.push_back(NULL);
	}
}