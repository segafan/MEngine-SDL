#ifndef PROFILER_H
#define PROFILER_H

#include <iostream>

namespace Profiler
{
	void Start(const unsigned int& ID);
	void Stop(const unsigned int& ID);
	void Stop(const unsigned int& ID, std::string text);
}

#endif