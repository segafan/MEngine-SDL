#include "Time.h"

#include "Config.h"

#if defined(OS_WINDOWS)
#include <Windows.h>
#include <iostream>
static double g_freq;
static bool g_timerInitialized = false;

#elif defined(OS_LINUX)
#include <sys/time.h>
static const long NANOSECONDS_PER_SECOND = 1000000000L;

#elif defined(OS_OTHER) && defined(CPP11_SUPPORT)
#include <chrono>
static std::chrono::system_clock::time_point m_epoch = std::chrono::high_resolution_clock::now();

#elif defined(OS_OTHER)
#include <SDL2/SDL.h>

#endif

double Time::GetTime()
{
#if defined(OS_WINDOWS)
	if (!g_timerInitialized)
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			std::cerr << "QueryPerformanceFrequency failed in timer initialization" << std::endl;

		g_freq = double(li.QuadPart);
		g_timerInitialized = true;
	}

	LARGE_INTEGER li;
	if (!QueryPerformanceCounter(&li))
		std::cerr << "QueryPerformanceCounter failed in get time!" << std::endl;

	return double(li.QuadPart) / g_freq;

#elif defined(OS_LINUX)
	timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (double)(((long)ts.tv_sec * NANOSECONDS_PER_SECOND) + ts.tv_nsec) / ((double)(NANOSECONDS_PER_SECOND));

#elif defined(OS_OTHER) && defined(CPP11_SUPPORT)
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_epoch).count() / 1000000000.0;

#elif defined(OS_OTHER)
	return (double)SDL_GetTicks() / 1000.0;
#endif
}