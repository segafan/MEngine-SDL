#ifndef RECT_H
#define RECT_H

#include "Point.h"

#include <SDL.h>

class Rect
{
public:
	Rect()
	{
		Clear();
	}
	Rect(int x,int y,int w,int h)
	{
		SetPosition(x,y,w,h);
	}

	SDL_Rect& operator= (const SDL_Rect c)
	{
		return GetSDLRect();
	}

	SDL_Rect GetSDLRect()
	{
		SDL_Rect rect;

		rect.x = x;
		rect.y = y;
		rect.w = w;
		rect.h = h;

		return rect;
	}

	void SetPosition(int x,int y,int w,int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	void Clear()
	{
		SetPosition(0,0,0,0);
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
		leftB = rect.getX();
		rightB = rect.getX() + rect.getW();
		topB = rect.getY();
		bottomB = rect.getY() + rect.getH();
		
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
	bool Intersects(int x,int y,int w,int h)
	{
		return Intersects(CreateRect(x,y,w,h));
	}


	bool Contains(Rect rect)
	{
		if(rect.getX() > x && rect.getW() < w && rect.getY() > y && rect.getH() < h)
			return true;
		else
			return false;
	}
	bool Contains(Point point)
	{
		if(point.getX() > x && point.getX() < w && point.getY() > y && point.getY() < h)
			return true;
		else
			return false;
	}
	bool Contains(int x,int y,int w,int h)
	{
		Rect tempRect = CreateRect(x,y,w,h);
		return Contains(tempRect);
	}

	static Rect CreateRect(int x,int y,int w,int h)
	{
		Rect tempRect(x,y,w,h);
		return tempRect;
	}

	Point Position()
	{
		Point point(x,y);
		return point;
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
		Point point(x + (w / 2), y + (h / 2));
		return point;
	}

	int Left()
	{
		return x;
	}
	int Right()
	{
		return (x + w);
	}
	int Top()
	{
		return y;
	}
	int Bottom()
	{
		return (y + h);
	}

	int Perimiter()
	{
		return (w + w + h + h);
	}
	int Area()
	{
		return (w * h);
	}

	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getW()
	{
		return w;
	}
	int getH()
	{
		return h;
	}

	void setX(int x)
	{
		this->x = x;
	}
	void setY(int y)
	{
		this->y = y;
	}
	void setW(int w)
	{
		this->w = w;
	}
	void setH(int h)
	{
		this->h = h;
	}

	int x,y,w,h;
};

#endif