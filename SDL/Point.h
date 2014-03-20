#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point()
	{
		Clear();
	}
	Point(int x,int y)
	{
		SetPosition(x,y);
	}


	void SetPosition(int x,int y)
	{
		this->x = x;
		this->y = y;
	}
	void Clear()
	{
		SetPosition(0,0);
	}


	bool Intersects(Point point)
	{
		if(x == point.getX() && y == point.getY())
			return true;
		else
			return false;
	}
	bool Intersects(int x,int y)
	{
		return Intersects(CreatePoint(x,y));
	}


	Point CreatePoint(int x,int y)
	{
		Point point(x,y);
		return point;
	}

	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}

	void setX(int x)
	{
		this->x = x;
	}
	void setY(int y)
	{
		this->y = y;
	}

	int x,y;
};

#endif