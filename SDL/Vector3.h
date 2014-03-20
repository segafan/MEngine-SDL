#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math.h"

class Vector3
{
public:
	Vector3()
	{
		SetPosition(0,0,0);
	}
	Vector3(float x,float y,float z)
	{
		SetPosition(x,y,z);
	}

	float Length()
	{
		return sqrt((float)( (x * x) + (y * y) + (z * z) ));
	}
	float Dot(Vector3 vector)
	{
		return (x * vector.getX() + y * vector.getY() + z * vector.getZ());
	}
	Vector3 Cross(Vector3 vector)
	{
		float x1 = (y * vector.getZ() - z * vector.getY());
		float y1 = (z * vector.getX() - x * vector.getZ());
		float z1 = (x * vector.getY() - y * vector.getX());

		return CreateVector(x1,y1,z1);
	}

	Vector3 Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;

		return Clone();
	}

	Vector3 Rotate()
	{
		return CreateVector(0,0,0);
	}

	Vector3 Clone()
	{
		CreateVector(x,y,z);
	}

	Vector3 Add(Vector3 vector)
	{
		return CreateVector(x + vector.getX(),y + vector.getY(),z + vector.getZ());
	}
	Vector3 Sub(Vector3 vector)
	{
		return CreateVector(x - vector.getX(),y - vector.getY(),z - vector.getZ());
	}
	Vector3 Mul(Vector3 vector)
	{
		return CreateVector(x * vector.getX(),y * vector.getY(),z * vector.getZ());
	}
	Vector3 Div(Vector3 vector)
	{
		return CreateVector(x / vector.getX(),y / vector.getY(),z / vector.getZ());
	}

	Vector3 Add(float value)
	{
		return CreateVector(x + value,y + value,z + value);
	}
	Vector3 Sub(float value)
	{
		return CreateVector(x - value,y - value,z - value);
	}
	Vector3 Mul(float value)
	{
		return CreateVector(x * value,y * value,z * value);
	}
	Vector3 Div(float value)
	{
		return CreateVector(x / value,y / value,z / value);
	}

	void SetPosition(float x,float y,float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getZ()
	{
		return z;
	}

	void setX(float x)
	{
		this->x = x;
	}
	void setY(float y)
	{
		this->y = y;
	}
	void setZ(float z)
	{
		this->z = z;
	}

	Vector3& operator+=(const Vector3& r)
	{
		x += r.x;
		y += r.y;
		z += r.z;

		return *this;
	}
	Vector3& operator-=(const Vector3& r)
	{
		x -= r.x;
		y -= r.y;
		z -= r.z;

		return *this;
	}
	Vector3& operator*=(float f)
	{
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}
	Vector3& operator/=(float f)
	{
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}

	Vector3 operator+(const Vector3& r) const 
	{
			Vector3 ret(x + r.x,
									 y + r.y,
									 z + r.z);

			return ret;
	}
	Vector3 operator-(const Vector3& r) const 
	{
			Vector3 ret(x - r.x,
									 y - r.y,
									 z - r.z);
			return ret;
	}
	Vector3 operator*(float f) const
	{
			Vector3 ret(x * f,
									 y * f,
									 z * f);
			return ret;
	}
	Vector3 operator/(float f) const 
	{
			Vector3 ret(x / f,
									 y / f,
									 z / f);
			return ret;
	}

	inline bool operator==(const Vector3& r) const
	{
			return x == r.x && y == r.y && z == r.z;
	}
	inline bool operator!=(const Vector3& r) const
	{
			return !operator==(r);
	}


	float x,y,z;
private:
	Vector3 CreateVector(float x,float y,float z)
	{
		Vector3 vector(x,y,z);
		return vector;
	}
};

#endif