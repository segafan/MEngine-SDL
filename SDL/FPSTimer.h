#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"

//TODO: Add better Time System & Create a Time.h

class FPSTimer
{
public:
	FPSTimer(float FramesPerSecond)
	{
		FPS = FramesPerSecond;
		frameTime = (1.0f / FPS) + 0.00001;
	}
	FPSTimer()
	{
		FPS = 60;
		frameTime = (1.0f / FPS) + 0.00001;
	}
	~FPSTimer()
	{

	}

	void SetFPS(float FramesPerSecond)
	{
		FPS = FramesPerSecond;
	}

	void Reset()
	{
		timer.Reset();
	}

	void Start()
	{
		timer.Start();
	}

	bool Tick()
	{
		if (FPS == 0)
			return true;

		if (frameTime <= timer.GetTicks())
		{
			timer.Reset();
			return true;
		}
		else if (frameTime - 1 > timer.GetTicks())
		{
			//TODO: test if frameTime - 1 is good and do something better than this
			SDL_Delay(1);
			return false;
		}
		else
			return false;
	}

private:
	Timer timer;
	float FPS;

	double frameTime;
};

inline void FPSCounter(Timer *timer)
{
	static unsigned int frames = 0;
	frames++;

	if ((timer->GetTicks() >= 1))
	{
		std::cout << "FPS " << frames << std::endl;
		timer->Reset();
		frames = 0;
	}
}

#endif
