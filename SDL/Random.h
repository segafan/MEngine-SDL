#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

inline bool IsRandomSafe()
{
	return (sizeof(time_t) > 4);
}

inline void InitRandom()
{
	std::srand((unsigned)std::time(nullptr));
}

inline int RandomNumber(int min, int max)
{
	int range = (max - min) + 1;

	return ((rand() % range) + min);
}

inline int RandomNumber(int max)
{
	return ((std::rand() % max) + 1);
}

inline bool RandomBool()
{
	return (RandomNumber(0, 1) == 0);
}

#endif