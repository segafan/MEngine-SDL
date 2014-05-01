#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <cstring>
#include <fstream>
#include <iostream>

#include <sstream>

#include <stdlib.h>

#if (_MSC_VER >= 1400)
#pragma warning(push)
#pragma warning(disable: 4996)
#endif 

inline std::string GetClockTime(void)
{
	time_t now;
	char the_date[12];

	the_date[0] = '\0';

	now = time(NULL);

	if (now != -1)
	{
		strftime(the_date, 12, "%H:%M:%S", localtime(&now));
	}

	return std::string(the_date);
}

inline std::string GetPrintTime(void)
{
	std::string time = ("[" + GetClockTime() + "] ");
	return time;
}

inline std::string GetDate(void)
{
	time_t now;
	char the_date[12];

	the_date[0] = '\0';

	now = time(NULL);

	if (now != -1)
	{
		strftime(the_date, 12, "%Y-%m-%d", localtime(&now));
	}

	return std::string(the_date);
}

#if (_MSC_VER >= 1400)
#pragma warning(pop)
#endif

inline int TextToNumber(const char * str)
{
	int val = 0;
	while (*str) 
	{
		val = val * 10 + (*str++ - '0');
	}
	return val;
}

template <typename T>
inline std::string NumberToString(T num)
{
	std::ostringstream strStream;
	strStream << num;
	return strStream.str();
}

inline bool FileExits(std::string filename)
{
	std::ifstream in(filename);
	
	if (!in)
	{
		in.close();
		return false;
	}
	else
	{
		in.close();
		return true;
	}
}

inline std::string GetLogName()
{
	std::string logStart = "logs/log-";
	std::string logEnd = ".txt";

	std::string date = GetDate();

	static int logNumber = 1;

	while (true)
	{
		std::string logname = (logStart + NumberToString(date) + "-" + NumberToString(logNumber) + logEnd);
			
		if (!FileExits(logname))
			break;

		if (logNumber > 500)
		{
			logNumber = 1;
			break;
		}

		logNumber++;
	}
	
	std::string fullLogName = (logStart + NumberToString(date) + "-" + NumberToString(logNumber) + logEnd);

	std::cout << "Available Log Name: " << fullLogName << std::endl;

	return fullLogName;
}

class Logger
{
public:
	Logger()
	{
		Open();
	}
	~Logger()
	{
		out.close();
	}

	void Open()
	{
		out.open(GetLogName());
		if (!out.is_open())
			std::cout << "Couldn't Open Log!" << std::endl;
		else
			std::cout << "Logging Started!" << std::endl << std::endl;
	}

	void LogLine(std::string message)
	{
		std::cout << GetPrintTime() << message << std::endl;
		out << GetPrintTime() << message << std::endl;
	}
	void LogLine(std::string message, std::string message2)
	{
		std::cout << GetPrintTime() << message << message2 << std::endl;
		out << GetPrintTime() << message << message2 << std::endl;
	}
	void LogLine(std::string message, std::string message2, std::string message3)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << std::endl;
		out << GetPrintTime() << message << message2 << message3 << std::endl;
	}
	void LogLine(std::string message, std::string message2, std::string message3, std::string message4)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << std::endl;
		out << GetPrintTime() << message << message2 << message3 << message4 << std::endl;
	}
	void LogLine(std::string message, std::string message2, std::string message3, std::string message4, std::string message5)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << message5 << std::endl;
		out << GetPrintTime() << message << message2 << message3 << message4 << message5 << std::endl;
	}
	void LogLine(std::string message, std::string message2, std::string message3, std::string message4, std::string message5, std::string message6)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << message5 << message6 << std::endl;
		out << GetPrintTime() << message << message2 << message3 << message4 << message5 << message6 << std::endl;
	}

	void LogLineWithoutDate(std::string message)
	{
		std::cout << message << std::endl;
		out << message << std::endl;
	}
	void LogLineWithoutDate(std::string message, std::string message2)
	{
		std::cout << message << message2 << std::endl;
		out << message << message2 << std::endl;
	}
	void LogLineWithoutDate(std::string message, std::string message2, std::string message3)
	{
		std::cout << message << message2 << message3 << std::endl;
		out << message << message2 << message3 << std::endl;
	}

	void LogLineWithoutDate(std::string message, int major, int minor, int patch)
	{
		std::cout << message << major << "." << minor << "." << patch << std::endl;
		out << message << major << "." << minor << "." << patch << std::endl;
	}

	void NewLine()
	{
		LogLineWithoutDate("");
	}
private:
	std::ofstream out;
};

#endif