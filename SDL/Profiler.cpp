#include "Profiler.h"

#include <unordered_map>
#include "Time.h"

std::unordered_map<unsigned int, double> profileValues;

void Profiler::Start(const unsigned int& ID)
{
	profileValues[ID] = Time::GetTime();
}

void Profiler::Stop(const unsigned int& ID)
{
	double time = Time::GetTime() - profileValues[ID];
	std::cout << time << "s  = " << time * 1000 << "ms" << std::endl;
}

void Profiler::Stop(const unsigned int& ID, std::string text)
{
	double time = Time::GetTime() - profileValues[ID];
	std::cout << text.c_str() << " "<< time << "s  = " << time * 1000 << "ms" << std::endl;
}