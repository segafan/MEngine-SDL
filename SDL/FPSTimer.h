#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"

//TODO: Add better Time System & Create a Time.h

class FPSTimer
{
public:
	FPSTimer()
	{
		SetFPS(60.0f);
	}
	FPSTimer(float FramesPerSecond)
	{
		SetFPS(FramesPerSecond);
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

		if (m_frameTime <= m_timer.GetTicks())
		{
			m_timer.Restart();
			return true;
		}
		else if (m_frameTime - 0.001 > m_timer.GetTicks())
		{
			SDL_Delay(1);
			return false;
		}
		else
			return false;
	}

private:
	Timer m_timer;
	float m_FPS;

	double m_frameTime;
};

inline void FPSCounter(Timer *timer)
{
	static unsigned int frames = 0;
	frames++;

	if ((timer->GetTicks() >= 1.0f))
	{
		std::cout << "FPS " << frames << std::endl;
		timer->Restart();
		frames = 0;
	}
}

#endif
