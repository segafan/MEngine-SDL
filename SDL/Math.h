#ifndef MATH_H
#define MATH_H

#include <cmath>

#define PI 3.141592653589793238462

#define DEG2RAD 0.01745329251994329576923690768f
#define RAD2DEG 57.2957795130823208767981548141f

inline float ToRadian(const float Degree)
{
	return (Degree * DEG2RAD);
}

inline float ToDegree(const float Radian)
{
	return (Radian * RAD2DEG);
}

#endif