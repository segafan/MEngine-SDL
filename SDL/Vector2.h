#ifndef VECTOR2_H
#define VECTOR2_H

#include "Math.h"

class Vector2
{
public:
	Vector2()
	{
		Clear();
	}
	Vector2(float x, float y)
	{
		SetPosition(x,y);
	}

	float Length()
	{
		return (float)sqrt((float)(x * x) + (y * y));
	}
	float Dot(Vector2& vector)
	{
		return (x * vector.getX() + y * vector.getY());
	}
	
	Vector2& operator+ (Vector2& vector)
	{
		return CreateVector(x + vector.getX(), y + vector.getY());
	}
	Vector2& operator- (Vector2& vector)
	{
		return CreateVector(x - vector.getX(), y - vector.getY());
	}
	Vector2& operator* (Vector2& vector)
	{
		return CreateVector(x * vector.getX(), y * vector.getY());
	}
	Vector2& operator/ (Vector2& vector)
	{
		return CreateVector(x / vector.getX(), y / vector.getY());
	}

	Vector2& Add(Vector2& vector)
	{
		return CreateVector(x + vector.getX(),y + vector.getY());
	}
	Vector2& Sub(Vector2& vector)
	{
		return CreateVector(x - vector.getX(),y - vector.getY());
	}
	Vector2& Mul(Vector2& vector)
	{
		return CreateVector(x * vector.getX(),y * vector.getY());
	}
	Vector2& Div(Vector2& vector)
	{
		return CreateVector(x / vector.getX(),y / vector.getY());
	}

	Vector2& Add(float value)
	{
		return CreateVector(x + value,y + value);
	}
	Vector2& Sub(float value)
	{
		return CreateVector(x - value,y - value);
	}
	Vector2& Mul(float value)
	{
		return CreateVector(x * value,y * value);
	}
	Vector2& Div(float value)
	{
		return CreateVector(x / value,y / value);
	}

	Vector2& Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;

		return Clone();
	}

	Vector2& Rotate(float angle)
	{
		float radian = (float)ToRadian(angle);
		float cosine = (float)cos(radian);
		float sine   = (float)sin(radian);

		return CreateVector((float)(x * cosine - y * sine),(float)(x * sine + y * cosine));
	}

	Vector2& Clone()
	{
		return CreateVector(x,y);
	}

	inline void SetPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	void Clear()
	{
		SetPosition(0,0);
	}

	inline float getX()
	{
		return x;
	}
	inline float getY()
	{
		return y;
	}
	
	inline void setX(float x)
	{
		this->x = x;
	}
	inline void setY(float y)
	{
		this->y = y;
	}

	static Vector2 CreateVector(float x, float y)
	{
		Vector2 vector(x,y);
		return vector;
	}

	float x, y;
};

#endif