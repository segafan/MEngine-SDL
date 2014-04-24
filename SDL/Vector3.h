#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math.h"

class Vector3
{
public:
	Vector3()
	{
		SetPosition(0, 0, 0);
	}
	Vector3(float x, float y, float z)
	{
		SetPosition(x, y, z);
	}

	float Length()
	{
		return sqrt((float)( (x * x) + (y * y) + (z * z) ));
	}
	float Dot(Vector3& vector)
	{
		return (x * vector.getX() + y * vector.getY() + z * vector.getZ());
	}
	Vector3& Cross(Vector3& vector)
	{
		float x1 = (y * vector.getZ() - z * vector.getY());
		float y1 = (z * vector.getX() - x * vector.getZ());
		float z1 = (x * vector.getY() - y * vector.getX());

		return CreateVector(x1, y1, z1);
	}

	Vector3& Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;

		return Clone();
	}

	Vector3& Rotate()
	{
		return CreateVector(0,0,0);
	}

	Vector3& Clone()
	{
		CreateVector(x,y,z);
	}

	Vector3& operator+ (Vector3& vector)
	{
		return CreateVector(x + vector.getX(), y + vector.getY(), z + vector.getZ());
	}
	Vector3& operator- (Vector3& vector)
	{
		return CreateVector(x - vector.getX(), y - vector.getY(), z - vector.getZ());
	}
	Vector3& operator* (Vector3& vector)
	{
		return CreateVector(x * vector.getX(), y * vector.getY(), z * vector.getZ());
	}
	Vector3& operator/ (Vector3& vector)
	{
		return CreateVector(x / vector.getX(), y / vector.getY(), z / vector.getZ());
	}

	Vector3& Add(Vector3& vector)
	{
		return CreateVector(x + vector.getX(),y + vector.getY(),z + vector.getZ());
	}
	Vector3& Sub(Vector3& vector)
	{
		return CreateVector(x - vector.getX(),y - vector.getY(),z - vector.getZ());
	}
	Vector3& Mul(Vector3& vector)
	{
		return CreateVector(x * vector.getX(),y * vector.getY(),z * vector.getZ());
	}
	Vector3& Div(Vector3& vector)
	{
		return CreateVector(x / vector.getX(),y / vector.getY(),z / vector.getZ());
	}

	Vector3& Add(float value)
	{
		return CreateVector(x + value,y + value,z + value);
	}
	Vector3& Sub(float value)
	{
		return CreateVector(x - value,y - value,z - value);
	}
	Vector3& Mul(float value)
	{
		return CreateVector(x * value,y * value,z * value);
	}
	Vector3& Div(float value)
	{
		return CreateVector(x / value,y / value,z / value);
	}

	inline void SetPosition(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline float getX()
	{
		return x;
	}
	inline float getY()
	{
		return y;
	}
	inline float getZ()
	{
		return z;
	}

	inline void setX(float x)
	{
		this->x = x;
	}
	inline void setY(float y)
	{
		this->y = y;
	}
	inline void setZ(float z)
	{
		this->z = z;
	}

	inline bool operator==(const Vector3& r) const
	{
			return x == r.x && y == r.y && z == r.z;
	}
	inline bool operator!=(const Vector3& r) const
	{
			return !operator==(r);
	}

	static Vector3 CreateVector(float x, float y, float z)
	{
		Vector3 vector(x, y, z);
		return vector;
	}

	float x, y, z;
};

#endif