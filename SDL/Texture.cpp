#include "Texture.h"

Texture::Texture()
{
	m_texture = NULL;
}

Texture::Texture(Display* display, const std::string& filepath)
{
	m_texture = NULL;
	Load(display, filepath);
}

Texture::~Texture()
{
	if (m_texture != NULL)
		SDL_DestroyTexture(m_texture);

	m_texture = NULL;
}

void Texture::Load(Display* display, const std::string& filepath)
{
	if (m_texture != NULL)
	{
		//Log this
		LOG_DEBUG("That texture class has already a texture loaded in it! Filepath: " << filepath.c_str());
		return;
	}
	else
	{
		m_texture = IMG_LoadTexture(display->GetRenderer(), filepath.c_str());

		if (m_texture == NULL)
		{
			LOG_ERROR("Couldn't load Texture! Filepath: " << filepath.c_str());
		}
	}
}

void Texture::Destroy()
{
	if (m_texture == NULL)
	{
		std::cout << "You can't Destroy the texture because it doesn't exist or it was already destroyed!" << std::endl;
	}
	else
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
	}
}

bool Texture::IsEmpty()
{
	return ((m_texture == NULL) || (m_texture == nullptr));
}

SDL_Texture* Texture::GetTexture()
{
	if (m_texture != NULL)
		return m_texture;
	else
		return NULL;
}