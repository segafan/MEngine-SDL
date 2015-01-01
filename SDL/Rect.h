//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef RECT_H
#define RECT_H

#include "Point.h"

#include "Util.h"
#include <iostream>

#include <SDL2/SDL.h>

class Rect
{
public:
	Rect()
	{
		Clear();
	}
	Rect(int x, int y, int w, int h)
	{
		SetPosition(x, y, w, h);
	}

	Rect operator+ (Rect& rect)
	{
		return Rect(this->x + rect.x, this->y + rect.y, w, h);
	}
	Rect operator- (Rect& rect)
	{
		return Rect(this->x - rect.x, this->y - rect.y, w, h);;
	}

	SDL_Rect& operator= (const SDL_Rect c)
	{
		return *ToSDLRect();
	}

	SDL_Rect* ToSDLRect()
	{
		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		return &rect;
	}

	const std::string ToString()
	{
		std::string toString = "";

		toString += "( ";
		toString += NumberToString(x);
		toString += " , ";
		toString += NumberToString(y);
		toString += " , ";
		toString += NumberToString(w);
		toString += " , ";
		toString += NumberToString(h);
		toString += " )";

		return toString;
	}

	void Print()
	{
		std::cout << ToString() << std::endl;
	}

	inline void SetPosition(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	void Clear()
	{
		SetPosition(0, 0, 0, 0);
	}


	bool Intersects(Rect rect)
	{
		//The sides of the rectangles
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		//Calculate the sides of rect A
		leftA = x;
		rightA = x + w;
		topA = y;
		bottomA = y + h;
        
		//Calculate the sides of rect B
		leftB = rect.GetX();
		rightB = rect.GetX() + rect.GetW();
		topB = rect.GetY();
		bottomB = rect.GetY() + rect.GetH();
		
		if( bottomA <= topB )
			return false;
		if( topA >= bottomB )
			return false; 
		if( rightA <= leftB )
			return false;   
		if( leftA >= rightB )
			return false;
    
		return true;
	}
	bool Intersects(int x, int y, int w, int h)
	{
		return Intersects(CreateRect(x, y, w, h));
	}


	bool Contains(Rect& rect)
	{
		return (rect.GetX() > x && rect.GetW() < w && rect.GetY() > y && rect.GetH() < h);
	}
	bool Contains(Point& point)
	{
		return(point.getX() > x && point.getX() < w && point.getY() > y && point.getY() < h);
	}
	bool Contains(int x, int y, int w, int h)
	{
		Rect tempRect(x, y, w, h);
		return Contains(tempRect);
	}

	static Rect CreateRect(int x, int y, int w, int h)
	{
		Rect tempRect(x, y, w, h);
		return tempRect;
	}

	Point Position()
	{
		return Point(x, y);
	}

	int CenterX()
	{
		return (x + (w / 2));
	}
	int CenterY()
	{
		return (y + (h / 2));
	}

	Point Center()
	{
		return Point(x + (w / 2), y + (h / 2));
	}

	inline int Left()
	{
		return x;
	}
	inline int Right()
	{
		return (x + w);
	}
	inline int Top()
	{
		return y;
	}
	inline int Bottom()
	{
		return (y + h);
	}

	inline int Perimiter()
	{
		return (w + w + h + h);
	}
	inline int Area()
	{
		return (w * h);
	}

	inline int& GetX()
	{
		return x;
	}
	inline int& GetY()
	{
		return y;
	}
	inline int& GetW()
	{
		return w;
	}
	inline int& GetH()
	{
		return h;
	}

	inline void SetX(int x)
	{
		this->x = x;
	}
	inline void SetY(int y)
	{
		this->y = y;
	}
	inline void SetW(int w)
	{
		this->w = w;
	}
	inline void SetH(int h)
	{
		this->h = h;
	}

	inline void SetSize(int w, int h)
	{
		this->w = w;
		this->h = h;
	}

	inline void TranslateX(int x)
	{
		this->x += x;
	}
	inline void TranslateY(int y)
	{
		this->y += y;
	}
	inline void Translate(int x, int y)
	{
		this->x += x;
		this->y += y;
	}

	int x, y, w, h;

private:
	SDL_Rect rect;
};

#endif