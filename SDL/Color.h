//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

class Color
{
public:
	Color()
	{
		SetColor(0, 0, 0, 255);
	}
	Color(unsigned short r, unsigned short g, unsigned short b)
	{
		SetColor(r, g, b, 255);
	}
	Color(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		SetColor(r, g, b, a);
	}

	Color& operator= (SDL_Color& color)
	{
		SetColor(color.r, color.g, color.b, color.a);
		return (*this);
	}
	
	void SetColor(unsigned short r, unsigned short g, unsigned short b, unsigned short a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	SDL_Color& ToSDLColor()
	{
		color.r = (Uint8)r;
		color.g = (Uint8)g;
		color.b = (Uint8)b;
		color.a = (Uint8)a;

		return color;
	}

	unsigned short r;
	unsigned short g;
	unsigned short b;
	unsigned short a;

private:
	SDL_Color color;
};
#define Colour Color
#define ToSDLColour ToSDLColor


inline Color MapRGB(Uint8 r, Uint8 g, Uint8 b)
{
	return Color(r, g, b, 255);
}
inline Color MapRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return Color(r, g, b, a);
}


#endif