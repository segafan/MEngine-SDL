#include "Font.h"

Font::Font()
{
	this->font = nullptr;
	this->bitmapFont = nullptr;
	this->size = 0;
}

Font::Font(Display* display, const std::string& filepath, unsigned int size)
{
	this->font = nullptr;
	this->bitmapFont = nullptr;
	this->size = 0;
	Load(display, filepath, size);
}

Font::Font(Display* display, const std::string& filepath, unsigned int size, unsigned int numchar)
{
	this->font = nullptr;
	this->bitmapFont = nullptr;
	this->size = 0;
	Load(display, filepath, size, numchar);
}

Font::~Font()
{
	Destroy();
}

void Font::Load(Display* display, const std::string& filepath, unsigned int size)
{
	Load(display, filepath, size, ASCII_EXTENDED);
}

void Font::Load(Display* display, const std::string& filepath, unsigned int size, unsigned int numchar)
{
	if (font != nullptr || bitmapFont != nullptr)
	{
		LOG_DEBUG("That font class has already a font loaded in it! Filepath: " << filepath << " Size: " << size);
		return;
	}

	font = TTF_OpenFont(filepath.c_str(), size);

	if (font == nullptr)
	{
		LOG_ERROR("Font couldn't be loaded! Filepath: " << filepath << " Size: " << size << " Error: " << SDL_GetError());
		font = nullptr;
		return;
	}

	this->size = size;
	LOG("Font loaded! Filepath: " << filepath << " Size: " << size);

	ConvertToBitmapFont(display, numchar);

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
	return ((bitmapFont == NULL) || (bitmapFont == nullptr));
}

void Font::ConvertToBitmapFont(Display* display, int numchar)
{
	int textureW = size * sqrt(numchar);
	int textureH = size * sqrt(numchar);

	bitmapFont = SDL_CreateTexture(display->GetRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureW, textureH);

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

	if(SDL_RenderClear(display->GetRenderer()) == -1)
		LOG_ERROR("Couldn't clear texture when creating bitmap font!");

	display->PopRenderColor();

	int x = 0;
	int y = 0;	

	for (int i = 0; i < numchar; i++)
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
			if (i != 0)
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
		if (SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h) == -1)
		{
			LOG_ERROR("Couldn't query texture when creating bitmap font!");
		}

		if (x + pos.GetW() > textureW)
		{
			x = 0;
			y++;
		}
		if (y * pos.h > textureH)
		{
			LOG_ERROR("Can't render anymore letters to the texture it's full! Font size: " << size);
			SDL_DestroyTexture(texture);
			break;
		}

		pos.x = x;
		pos.y = y * pos.h;

		glyphPositions.push_back(pos);

		x += pos.GetW();

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

std::vector<Rect>& Font::GetGlyphPositions()
{
	return glyphPositions;
}

SDL_Texture* Font::GetBitmapFont()
{
	return bitmapFont;
}

Rect Font::GetTextSize(const std::wstring& text)
{
	int x = 0;
	int y = 0;
	int w = 0;
	int h = glyphPositions[97].GetH();
	int ID;
	for (int i = 0; i < text.length(); i++)
	{
		ID = text[i];
		if (ID < 0 || ID > (glyphPositions.size() - 1))
		{
			continue;
		}

		if (ID == 10)
		{
			y++;

			if (x > w)
				w = x;

			x = 0;
			continue;
		}

		x += glyphPositions[ID].GetW();
	}

	if (x > w)
		w = x;

	return Rect(0, 0, w, h * (y + 1));
}