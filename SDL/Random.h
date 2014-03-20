#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

bool isRandomSafe()
{
	if (sizeof(time_t) > 4)
		return true;
	else
		return false;
}

void InitRandom()
{
	std::srand((unsigned)std::time(nullptr));
}

int RandomNumber(int min, int max)
{
	int range = (max - min) + 1;

	return ((rand() % range) + min);
}

int RandomNumber(int max)
{
	return ((std::rand() % max) + 1);
}

#endif