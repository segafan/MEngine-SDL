#ifndef FPSTIMER_H
#define FPSTIMER_H

#include "Timer.h"

class FPSTimer
{
public:
	FPSTimer(float FramesPerSecond)
	{
		FPS = FramesPerSecond;
		frameTime = 1000.0f / FPS;
	}
	FPSTimer()
	{
		FPS = 60;
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

	void Update()
	{
		if (frameTime == NULL)
			frameTime = (1000.0f / FPS);

		if (FPS == 0)
			return;

		if (timer.GetTicks() < frameTime)
		{
			if ((frameTime - timer.GetTicks()) > 0)
			{
				SDL_Delay((Uint32)(frameTime - timer.GetTicks()));
			}
		}

		timer.Reset();
	}

private:
	Timer timer;
	float FPS;

	float frameTime;
};

inline void FPSCounter(Timer *timer)
{
	static unsigned short int frames = 0;

	if ((timer->GetTicks() > 1000))
	{
		std::cout << "FPS " << frames << std::endl;
		timer->Reset();
		frames = 0;
	}
	frames++;
}

#endif
