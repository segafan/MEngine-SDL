//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point()
	{
		Clear();
	}
	Point(int x, int y)
	{
		SetPosition(x, y);
	}


	inline void SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	void Clear()
	{
		SetPosition(0, 0);
	}


	bool Intersects(Point point)
	{
		return (x == point.getX() && y == point.getY());
	}
	bool Intersects(int x, int y)
	{
		return Intersects(CreatePoint(x, y));
	}


	static Point CreatePoint(int x, int y)
	{
		Point point(x, y);
		return point;
	}

	inline int getX()
	{
		return x;
	}
	inline int getY()
	{
		return y;
	}

	inline void setX(int x)
	{
		this->x = x;
	}
	inline void setY(int y)
	{
		this->y = y;
	}

	int x, y;
};

#endif