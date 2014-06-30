#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"

//TODO: Add better Time System & Create a Time.h

inline void FPSCounter();

class FPSTimer
{
public:
	FPSTimer()
	{
		SetFPS(60.0f);
		m_unprocessedTime = 0;
	}
	FPSTimer(float FramesPerSecond)
	{
		SetFPS(FramesPerSecond);
		m_unprocessedTime = 0;
	}
	~FPSTimer()
	{

	}

	void SetFPS(float FramesPerSecond)
	{
		m_FPS = FramesPerSecond;

		if (m_FPS > 0)
			m_frameTime = (double)(1.0f / m_FPS) + 0.00001;
		else
			m_frameTime = 0.0f;
	}

	void Start()
	{
		m_timer.Start();
	}
	void Stop()
	{
		m_timer.Stop();
	}

	void Restart()
	{
		m_timer.Restart();
	}

	bool Tick()
	{
		if (m_FPS <= 0)
			return true;

		m_unprocessedTime += m_timer.GetTicks();
		m_timer.Restart();

		if (m_unprocessedTime >= m_frameTime)
		{
			FPSCounter();

			m_unprocessedTime -= m_frameTime;
			return true;
		}
		else
		{
			SDL_Delay(1);
			return false;
		}
	}

private:
	Timer m_timer;
	float m_FPS;

	double m_frameTime;
	double m_unprocessedTime;
};

inline void FPSCounter()
{
	static double startTime = Time::GetTime();
	static unsigned int frames = 0;
	frames++;

	if ((Time::GetTime() - startTime >= 1.0f))
	{
		std::cout << "FPS " << frames << std::endl;
		startTime = Time::GetTime();
		frames = 0;
	}
}

#endif
