#ifndef QUATERNION_H
#define QUATERNION_H

#include "Math.h"
#include "Vector3.h"

class Quaternion
{
public:
	Quaternion()
	{
		SetPosition(0,0,0,0);
	}
	Quaternion(float x,float y,float z,float w)
	{
		SetPosition(x,y,z,w);
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

		return CreateQuarternion(x,y,z,w);
	}
	Quaternion Conjugate()
	{
		return CreateQuarternion(-x,-y,-z,w);
	}

	Quaternion Mul(Quaternion r)
	{
		float w_ = w * r.getW() - x * r.getX() - y * r.getY() - z * r.getZ();
        float x_ = x * r.getW() + w * r.getX() + y * r.getZ() - z * r.getY();
        float y_ = y * r.getW() + w * r.getY() + z * r.getX() - x * r.getZ();
        float z_ = z * r.getW() + w * r.getZ() + x * r.getY() - y * r.getX();

		return CreateQuarternion(x_,y_,z_,w_);
	}
	Quaternion Mul(Vector3 r)
	{
		float w_ = -x * r.getX() - y * r.getY() - z * r.getZ();
        float x_ =  w * r.getX() + y * r.getZ() - z * r.getY();
        float y_ =  w * r.getY() + z * r.getX() - x * r.getZ();
        float z_ =  w * r.getZ() + x * r.getY() - y * r.getX();
                
        return CreateQuarternion(x_,y_,z_,w_);
	}

	void SetPosition(float x,float y,float z,float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
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
	float getW()
	{
		return w;
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
	void setW(float w)
	{
		this->w = w;
	}
private:
	Quaternion CreateQuarternion(float x,float y,float z,float w)
	{
		Quaternion q(x,y,z,w);
		return q;
	}
	float x,y,z,w;
};

#endif