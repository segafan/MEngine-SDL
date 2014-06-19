#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
public:
	Timer()
	{
		interval = 1;
		started = false;
	}
	~Timer()
	{

	}

	void Reset()
	{
		startTime = SDL_GetTicks();
		time = 0;
	}

	void Start()
	{
		if (!started)
		{
			startTime = SDL_GetTicks();
			std::cout << "Timer Started: " << startTime << std::endl;

			started = true;
		}
	}

	void Stop()
	{
		if (started)
		{
			started = false;
		}
	}

	void SetInterval(float intervalMilliseconds)
	{
		if (started)
		{
			interval = intervalMilliseconds;
			std::cout << "Interval Set: " << interval << std::endl;
		}
		else
			std::cout << "Timer needs to be started before Interval can be set!" << std::endl;
	}

	unsigned int GetTicks()
	{
		if (started)
			time = SDL_GetTicks() - startTime;

		return (unsigned int)(time / interval);
	}
private:
	unsigned int startTime;
	unsigned int time;

	float interval;

	bool started;
};

#endif