#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

inline bool isRandomSafe()
{
	if (sizeof(time_t) > 4)
		return true;
	else
		return false;
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
	int random = RandomNumber(0, 1);
	
	if (random == 0)
		return true;
	else
		return false;
}
#endif