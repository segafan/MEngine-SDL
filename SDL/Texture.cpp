#include "Texture.h"

Texture::Texture()
{
	m_texture = NULL;
}

Texture::Texture(SDL_Renderer* renderer, const std::string& filepath)
{
	Load(renderer, filepath);
}

Texture::Texture(Display* display, const std::string& filepath)
{
	Load(display->GetRenderer(), filepath);
}

Texture::~Texture()
{
	if (m_texture != NULL)
		SDL_DestroyTexture(m_texture);

	m_texture = NULL;
}

void Texture::Load(SDL_Renderer* renderer, const std::string& filepath)
{
	if (m_texture != NULL)
	{
		//Log this
		LOG_DEBUG("That texture class has already a texture loaded in it! Filepath: " << filepath.c_str());
		return;
	}
	else
	{
		m_texture = IMG_LoadTexture(renderer, filepath.c_str());

		if (m_texture == NULL)
		{
			LOG_ERROR("Couldn't load Texture! Filepath: " << filepath.c_str());
		}
	}
}

void Texture::Load(Display* display, const std::string& filepath)
{
	Load(display->GetRenderer(), filepath);
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

void Texture::Draw(Display* display, Rect* pos)
{
	SDL_RenderCopy(display->GetRenderer(), m_texture, NULL, (*pos - display->GetCamera().GetView()).ToSDLRect());
}

void Texture::Draw(Display* display, Rect* src, Rect* pos)
{
	SDL_RenderCopy(display->GetRenderer(), m_texture, src->ToSDLRect(), (*pos - display->GetCamera().GetView()).ToSDLRect());
}

void Texture::DrawRotated(Display* display, Rect* pos, float angle)
{
	SDL_RenderCopyEx(display->GetRenderer(), m_texture, NULL, (*pos - display->GetCamera().GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void Texture::DrawRotated(Display* display, Rect* src, Rect* pos, float angle)
{
	SDL_RenderCopyEx(display->GetRenderer(), m_texture, src->ToSDLRect(), (*pos - display->GetCamera().GetView()).ToSDLRect(), angle, NULL, SDL_FLIP_NONE);
}

void Texture::DrawFlipped(Display* display, Rect* pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(display->GetRenderer(), m_texture, NULL, (*pos - display->GetCamera().GetView()).ToSDLRect(), NULL, NULL, flip);
}

void Texture::DrawFlipped(Display* display, Rect* src, Rect* pos, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(display->GetRenderer(), m_texture, src->ToSDLRect(), (*pos - display->GetCamera().GetView()).ToSDLRect(), NULL, NULL, flip);
}
