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
		return (x * vector.GetX() + y * vector.GetY() + z * vector.GetZ());
	}
	Vector3 Cross(Vector3& vector)
	{
		float x1 = (y * vector.GetZ() - z * vector.GetY());
		float y1 = (z * vector.GetX() - x * vector.GetZ());
		float z1 = (x * vector.GetY() - y * vector.GetX());

		return CreateVector(x1, y1, z1);
	}

	Vector3& Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;

		return (*this);
	}

	Vector3 Rotate()
	{
		return CreateVector(0, 0, 0);
	}

	Vector3& Clone()
	{
		return (*this);
	}

	Vector3 operator+ (Vector3& vector)
	{
		return CreateVector(x + vector.GetX(), y + vector.GetY(), z + vector.GetZ());
	}
	Vector3 operator- (Vector3& vector)
	{
		return CreateVector(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
	}
	Vector3 operator* (Vector3& vector)
	{
		return CreateVector(x * vector.GetX(), y * vector.GetY(), z * vector.GetZ());
	}
	Vector3 operator/ (Vector3& vector)
	{
		return CreateVector(x / vector.GetX(), y / vector.GetY(), z / vector.GetZ());
	}

	Vector3 operator+ (float value)
	{
		return CreateVector(x + value, y + value, z + value);
	}
	Vector3 operator- (float value)
	{
		return CreateVector(x - value, y - value, z - value);
	}
	Vector3 operator* (float value)
	{
		return CreateVector(x * value, y * value, z * value);
	}
	Vector3 operator/ (float value)
	{
		return CreateVector(x / value, y / value, z / value);
	}

	Vector3 Add(Vector3& vector)
	{
		return CreateVector(x + vector.GetX(), y + vector.GetY(), z + vector.GetZ());
	}
	Vector3 Sub(Vector3& vector)
	{
		return CreateVector(x - vector.GetX(), y - vector.GetY(), z - vector.GetZ());
	}
	Vector3 Mul(Vector3& vector)
	{
		return CreateVector(x * vector.GetX(), y * vector.GetY(), z * vector.GetZ());
	}
	Vector3 Div(Vector3& vector)
	{
		return CreateVector(x / vector.GetX(), y / vector.GetY(), z / vector.GetZ());
	}

	Vector3 Add(float value)
	{
		return CreateVector(x + value, y + value, z + value);
	}
	Vector3 Sub(float value)
	{
		return CreateVector(x - value, y - value, z - value);
	}
	Vector3 Mul(float value)
	{
		return CreateVector(x * value, y * value, z * value);
	}
	Vector3 Div(float value)
	{
		return CreateVector(x / value, y / value, z / value);
	}

	inline void SetPosition(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline float& GetX()
	{
		return x;
	}
	inline float& GetY()
	{
		return y;
	}
	inline float& GetZ()
	{
		return z;
	}

	inline void SetX(float x)
	{
		this->x = x;
	}
	inline void SetY(float y)
	{
		this->y = y;
	}
	inline void SetZ(float z)
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