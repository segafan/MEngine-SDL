#include "Logger.h"

std::string GetLogName()
{
	const std::string& logStart = "logs/log-";
	const std::string& logEnd = ".txt";

	const std::string& date = GetDate();

	//TODO: Make this thread-safe
	static int logNumber = 1;

	while (true)
	{
		std::string logname = (logStart + date + "-" + NumberToString(logNumber) + logEnd);

		if (!FileExits(logname))
			break;

		if (logNumber > 500)
		{
			//TODO ADD a,b,c... if it's more than 500
			logNumber = 1;
			break;
		}

		logNumber++;
	}

	std::string fullLogName = (logStart + date + "-" + NumberToString(logNumber) + logEnd);

	std::cout << "Available Log Name: " << fullLogName << std::endl;

	return fullLogName;
}

Logger* Logger::instance = NULL;

void Logger::Open()
{
	if (!out.is_open())
	{
		out.open(GetLogName().c_str());
		if (!out.is_open())
			std::cout << "Couldn't Open Log!" << std::endl;
		else
			std::cout << "Logging Started!" << std::endl << std::endl;
	}
}

void Logger::Log(const std::string& message)
{
	std::cout << GetPrintTime() << message;
	out << GetPrintTime() << message;
}

void Logger::LogPure(const std::string& message)
{
	std::cout << message;
	out << message;
}

void Logger::LogLine(const std::string& message)
{
	std::cout << GetPrintTime() << message << std::endl;
	out << GetPrintTime() << message << std::endl;
}

void Logger::LogLinePure(const std::string& message)
{
	std::cout << message << std::endl;
	out << message << std::endl;
}

void Logger::LogTime()
{
	std::cout << GetPrintTime();
	out << GetPrintTime();
}

void Logger::NewLine()
{
	std::cout << std::endl;
	out << std::endl;
}

Logger* Logger::Instance()
{
	if (!instance)
		instance = new Logger();

	return instance;
}

void Logger::ResetInstance()
{
	delete instance;
	instance = NULL;
}