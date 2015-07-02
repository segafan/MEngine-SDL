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
	Destroy();
}

void Texture::Load(Display* display, const std::string& filepath)
{
	if (!IsEmpty())
	{
		LOG_DEBUG("That texture class has already a texture loaded in it! Filepath: " << filepath.c_str());
		return;
	}
	else
	{
		m_texture = IMG_LoadTexture(display->GetRenderer(), filepath.c_str());

		if (IsEmpty())
		{
			LOG_ERROR("Couldn't load Texture! Filepath: " << filepath.c_str());
		}
		else
		{
			LOG("Texture loaded: " << filepath.c_str());
		}
	}
}

void Texture::Destroy()
{
	if (!IsEmpty())
		SDL_DestroyTexture(m_texture);

	m_texture = NULL;
}

bool Texture::IsEmpty()
{
	return ((m_texture == NULL) || (m_texture == nullptr));
}

SDL_Texture* Texture::GetTexture()
{
	if (!IsEmpty())
		return m_texture;
	else
		return NULL;
}

void Texture::SetAlpha(int alpha)
{
	if (SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND) == -1)
		LOG_ERROR("Couldn't set blend mode!");
	if(SDL_SetTextureAlphaMod(m_texture, alpha) == -1)
		LOG_ERROR("Couldn't set alpha mod!");
}

int Texture::GetAlpha()
{
	Uint8 alpha;

	if(SDL_GetTextureAlphaMod(m_texture, &alpha) == -1)
		LOG_ERROR("Couldn't get alpha mod");

	return alpha;
}