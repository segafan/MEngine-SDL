#ifndef MATH_H
#define MATH_H

#include <cmath>

#define PI 3.141592653589793238462

inline float toRad(float angle)
{
	return (float)((angle * PI) / 180);
}
inline float toAngle(float rad)
{
	return (float)((rad * 180) / PI);
}

#endif