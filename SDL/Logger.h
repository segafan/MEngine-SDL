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
	return static_cast<std::ostringstream*>(&(std::ostringstream() << num))->str();
}

inline bool FileExits(std::string filename)
{
	std::ifstream in(filename.c_str());
	
	//TODO: This MAY cause problems!
	bool isOpen = (bool)(in);

	in.close();

	return isOpen;
}

inline std::string GetLogName()
{
	std::string logStart = "logs/log-";
	std::string logEnd = ".txt";

	std::string date = GetDate();

	int logNumber = 1;

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
		out.open(GetLogName().c_str());
		if (!out.is_open())
			std::cout << "Couldn't Open Log!" << std::endl;
		else
			std::cout << "Logging Started!" << std::endl << std::endl;
	}

	//Log
	template<class I>
	Logger& Log(I message)
	{
		std::cout << message;
		out		  << message;
		return (*this);
	}
	template<class I, class U>
	Logger& Log(I message, U message2)
	{
		std::cout << message << message2;
		out		  << message << message2;
		return (*this);
	}
	template<class I, class U, class J>
	Logger& Log(I message, U message2, J message3)
	{
		std::cout << message << message2 << message3;
		out		  << message << message2 << message3;
		return (*this);
	}
	template<class I, class U, class J, class K>
	Logger& Log(I message, U message2, J message3, K message4)
	{
		std::cout << message << message2 << message3 << message4;
		out		  << message << message2 << message3 << message4;
		return (*this);
	}
	template<class I, class U, class J, class K, class M>
	Logger& Log(I message, U message2, J message3, K message4, M message5)
	{
		std::cout << message << message2 << message3 << message4 << message5;
		out		  << message << message2 << message3 << message4 << message5;
		return (*this);
	}
	template<class I, class U, class J, class K, class M, class L>
	Logger& Log(I message, U message2, J message3, K message4, M message5, L message6)
	{
		std::cout << message << message2 << message3 << message4 << message5 << message6;
		out		  << message << message2 << message3 << message4 << message5 << message6;
		return (*this);
	}

	//Log Line
	template<class I>
	Logger& LogLine(I message)
	{
		std::cout << GetPrintTime() << message << std::endl;
		out		  << GetPrintTime() << message << std::endl;
		return (*this);
	}
	template<class I, class U>
	Logger& LogLine(I message, U message2)
	{
		std::cout << GetPrintTime() << message << message2 << std::endl;
		out		  << GetPrintTime() << message << message2 << std::endl;
		return (*this);
	}
	template<class I, class U, class J>
	Logger& LogLine(I message, U message2, J message3)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << std::endl;
		out		  << GetPrintTime() << message << message2 << message3 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K>
	Logger& LogLine(I message, U message2, J message3, K message4)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << std::endl;
		out		  << GetPrintTime() << message << message2 << message3 << message4 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K, class M>
	Logger& LogLine(I message, U message2, J message3, K message4, M message5)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << message5 << std::endl;
		out		  << GetPrintTime() << message << message2 << message3 << message4 << message5 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K, class M, class L>
	Logger& LogLine(I message, U message2, J message3, K message4, M message5, L message6)
	{
		std::cout << GetPrintTime() << message << message2 << message3 << message4 << message5 << message6 << std::endl;
		out		  << GetPrintTime() << message << message2 << message3 << message4 << message5 << message6 << std::endl;
		return (*this);
	}

	//Log Line without Time
	template<class I>
	Logger& LogLineWithoutTime(I message)
	{
		std::cout << message << std::endl;
		out		  << message << std::endl;
		return (*this);
	}
	template<class I, class U>
	Logger& LogLineWithoutTime(I message, U message2)
	{
		std::cout << message << message2 << std::endl;
		out		  << message << message2 << std::endl;
		return (*this);
	}
	template<class I, class U, class J>
	Logger& LogLineWithoutTime(I message, U message2, J message3)
	{
		std::cout << message << message2 << message3 << std::endl;
		out		  << message << message2 << message3 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K>
	Logger& LogLineWithoutTime(I message, U message2, J message3, K message4)
	{
		std::cout << message << message2 << message3 << message4 << std::endl;
		out		  << message << message2 << message3 << message4 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K, class M>
	Logger& LogLineWithoutTime(I message, U message2, J message3, K message4, M message5)
	{
		std::cout << message << message2 << message3 << message4 << message5 << std::endl;
		out		  << message << message2 << message3 << message4 << message5 << std::endl;
		return (*this);
	}
	template<class I, class U, class J, class K, class M, class L>
	Logger& LogLineWithoutTime(I message, U message2, J message3, K message4, M message5, L message6)
	{
		std::cout << message << message2 << message3 << message4 << message5 << message6 << std::endl;
		out		  << message << message2 << message3 << message4 << message5 << message6 << std::endl;
		return (*this);
	}

	//Other Logs
	Logger& LogVersion(std::string message, int major, int minor, int patch)
	{
		std::cout << message << major << "." << minor << "." << patch << std::endl;
		out		  << message << major << "." << minor << "." << patch << std::endl;
		return (*this);
	}

	Logger& LogTime()
	{
		std::cout << GetPrintTime();
		out		  << GetPrintTime();
		return (*this);
	}

	Logger& NewLine()
	{
		LogLineWithoutTime("");
		return (*this);
	}
private:
	std::ofstream out;
};

#endif