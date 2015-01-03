#include "Random.h"

#ifdef CPP11_SUPPORT

#include <random>

static std::mt19937 generator;

bool Random::IsSafe()
{
	return true;
}

void Random::Init()
{
	generator.seed(std::random_device()());
}

int Random::Number(int min, int max)
{
	std::uniform_int_distribution<std::mt19937::result_type> range(min, max);
	return range(generator);
}

int Random::Number(int max)
{
	std::uniform_int_distribution<std::mt19937::result_type> range(0, max);
	return range(generator);
}

bool Random::Bool()
{
	return (generator() % 2) == 0;
}

#else

#include <ctime>
#include <cstdlib>

bool Random::IsSafe()
{
	return (sizeof(time_t) > 4);
}

void Random::Init()
{
	std::srand((unsigned)std::time(nullptr));
}

int Random::Number(int min, int max)
{
	return ((std::rand() % ((max - min) + 1)) + min);
}

int Random::Number(int max)
{
	return (std::rand() % max);
}

bool Random::Bool()
{
	return ((std::rand() % 2) == 0);
}

#endif