#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include "Time.h"

class Timer
{
public:
	Timer()
	{
		started = false;
	}
	~Timer()
	{

	}

	void Reset()
	{
		startTime = Time::GetTime();
		time = 0;
	}

	void Start()
	{
		if (!started)
		{
			startTime = Time::GetTime();
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

	double GetTicks()
	{
		if (started)
			time = Time::GetTime() - startTime;

		return time;
	}
private:
	double startTime;
	double time;

	bool started;
};

#endif