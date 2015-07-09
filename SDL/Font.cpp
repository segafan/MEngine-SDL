#include "Font.h"

Font::Font()
{
	font = nullptr;
	bitmapFont = nullptr;
	size = 0;
}

Font::~Font()
{
	Destroy();
}

void Font::Load(Display* display, const std::string& filepath, unsigned int size)
{
	if (font != nullptr || bitmapFont != nullptr)
	{
		LOG_DEBUG("That font class has already a font loaded in it! Filepath: " << filepath << " Size: " << size);
		return;
	}

	font = TTF_OpenFont(filepath.c_str(), size);

	if (font == nullptr)
	{
		LOG_ERROR("Font couldn't be loaded! Filepath: " << filepath << " Size: " << size);
		font = nullptr;
		return;
	}

	this->size = size;
	LOG("Font loaded! Filepath: " << filepath << " Size: " << size);

	ConvertToBitmapFont(display);

	TTF_CloseFont(font);
	font = nullptr;
}

void Font::Destroy()
{
	if (font != nullptr)
		TTF_CloseFont(font);

	font = nullptr;

	if (bitmapFont != nullptr)
		SDL_DestroyTexture(bitmapFont);

	bitmapFont = nullptr;
}

bool Font::IsEmpty()
{
	return ((font == nullptr) || (bitmapFont == nullptr));
}

void Font::ConvertToBitmapFont(Display* display)
{
	bitmapFont = SDL_CreateTexture(display->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size * 32, size * 32);

	if (bitmapFont == nullptr)
	{
		LOG_ERROR("Couldn't create texture for bitmap font creating!");
	}

	if(SDL_SetTextureBlendMode(bitmapFont, SDL_BLENDMODE_BLEND) == -1)
		LOG_ERROR("Couldn't set blendmode for texture when creating bitmap font!");


	if(SDL_SetRenderTarget(display->GetRenderer(), bitmapFont) == -1)
		LOG_ERROR("Couldn't set render target to texture when creating bitmap font!");

	display->PushRenderColor();
	display->SetRenderColor(255, 255, 255, 0);

	if(SDL_RenderClear(display->GetRenderer()) == -1);
		LOG_ERROR("Couldn't clear texture when creating bitmap font!");

	display->PopRenderColor();

	int x = 0;
	int y = 0;

	for (int i = 0; i <= 128; i++)
	{	
		//If break line charater skip
		if (i == 10)
		{ 
			glyphPositions.push_back(Rect(0, 0, 0, 0));
			continue;
		}

		SDL_Surface* surface = nullptr;
		surface = TTF_RenderGlyph_Blended(font, i, COLOR_WHITE.ToSDLColor());

		if (surface == nullptr)
		{
			//Don't show error on the NULL character
			if (i == 0)
			{
				LOG_ERROR("Couldn't create glyph surface! Using letter " << (char)i);
			}
			glyphPositions.push_back(Rect(0, 0, 0, 0));
			continue;
		}

		SDL_Texture* texture = nullptr;
		texture = SDL_CreateTextureFromSurface(display->GetRenderer(), surface);

		SDL_FreeSurface(surface);

		if (texture == nullptr)
		{
			LOG_ERROR("Couldn't create glyph texture! Using letter " << (char)i);
			glyphPositions.push_back(Rect(0, 0, 0, 0));
			continue;
		}

		Rect pos;
		if(SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h) == -1)
			LOG_ERROR("Couldn't query texture when creating bitmap font!");
		pos.x = x;
		pos.y = y * pos.h;

		glyphPositions.push_back(pos);

		x += pos.GetW();

		if (x > (size * 32) - (size * 1.4))
		{
			x = 0;
			y++;
		}

		if (y * pos.h > (size * 32) - (size * 1.4))
		{
			LOG_ERROR("Can't render anymore letters to the texture it's full! Font size: " << size);
			SDL_DestroyTexture(texture);
			break;
		}

		//Don't render tab character
		if (i != 9)
		{
			if (SDL_RenderCopy(display->GetRenderer(), texture, NULL, pos.ToSDLRect()) == -1)
				LOG_ERROR("Couldn't draw on texture when creating bitmap font!");
		}

		SDL_DestroyTexture(texture);
	}

	if(SDL_SetRenderTarget(display->GetRenderer(), NULL) == -1)
		LOG_ERROR("Couldn't set render target back to renderer when creating bitmap font!");
	
	return;
}