#ifndef QUATERNION_H
#define QUATERNION_H

#include "Math.h"
#include "Vector3.h"

class Quaternion
{
public:
	Quaternion()
	{
		SetPosition(0, 0, 0, 0);
	}
	Quaternion(float x, float y, float z, float w)
	{
		SetPosition(x, y, z, w);
	}

	float Length()
	{
		return (float)sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion Normalize()
	{
		float length = Length();

		x /= length;
		y /= length;
		z /= length;
		w /= length;

		return CreateQuarternion(x, y, z, w);
	}
	Quaternion Conjugate()
	{
		return CreateQuarternion(-x, -y, -z, w);
	}

	Quaternion Mul(Quaternion& r)
	{
		float w_ = w * r.GetW() - x * r.GetX() - y * r.GetY() - z * r.GetZ();
        float x_ = x * r.GetW() + w * r.GetX() + y * r.GetZ() - z * r.GetY();
        float y_ = y * r.GetW() + w * r.GetY() + z * r.GetX() - x * r.GetZ();
        float z_ = z * r.GetW() + w * r.GetZ() + x * r.GetY() - y * r.GetX();

		return CreateQuarternion(x_, y_, z_, w_);
	}
	Quaternion Mul(Vector3& r)
	{
		float w_ = -x * r.GetX() - y * r.GetY() - z * r.GetZ();
        float x_ =  w * r.GetX() + y * r.GetZ() - z * r.GetY();
        float y_ =  w * r.GetY() + z * r.GetX() - x * r.GetZ();
        float z_ =  w * r.GetZ() + x * r.GetY() - y * r.GetX();
                
		return CreateQuarternion(x_, y_, z_, w_);
	}

	inline void SetPosition(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
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
	inline float& GetW()
	{
		return w;
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
	inline void SetW(float w)
	{
		this->w = w;
	}

	static Quaternion CreateQuarternion(float x, float y, float z, float w)
	{
		Quaternion q(x, y, z, w);
		return q;
	}

private:
	float x, y, z, w;
};

#endif