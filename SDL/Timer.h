#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include "Time.h"

//TODO: Add Pause and Resume and Interval
class Timer
{
public:
	Timer()
	{
		m_started = false;

		m_startTime = 0;
	}
	~Timer()
	{

	}

	void Start()
	{
		if (!m_started)
		{
			m_started = true;
			m_startTime = Time::GetTime();
		}
	}
	void Stop()
	{
		if (m_started)
			m_started = false;
	}

	void Restart()
	{
		Stop();
		Start();
	}

	double GetTicks()
	{
		if (m_started)
			return Time::GetTime() - m_startTime;
		else
			return 0;
	}

private:
	bool m_started;

	double m_startTime;
};

#endif