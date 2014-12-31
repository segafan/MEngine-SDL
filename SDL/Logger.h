//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef LOGGER_H
#define LOGGER_H

#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Util.h"

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

inline bool FileExits(std::string filename)
{
	std::ifstream in(filename.c_str());

	//TODO: This MAY cause problems!
	bool isOpen = (bool)(in);

	in.close();

	return isOpen;
}

class Logger
{
public:
	void Open();

	void Log(const std::string& message);

	void LogPure(const std::string& message);

	void LogLine(const std::string& message);

	void LogLinePure(const std::string& message);

	void LogTime();

	void NewLine();

	static Logger* Instance();
	static void ResetInstance();

private:
	Logger() {};
	Logger(Logger const&){};
	Logger& operator=(Logger const&){};

	static Logger* instance;

	std::ofstream out;
};

#define LOG(Message_) Logger::Instance()->LogLine(static_cast<std::ostringstream&>(std::ostringstream().flush() << Message_).str());
#define LOG_PURE(Message_) Logger::Instance()->LogLinePure(static_cast<std::ostringstream&>(std::ostringstream().flush() << Message_).str());
#define LOG_DEBUG(Message_) Logger::Instance()->LogLine(static_cast<std::ostringstream&>(std::ostringstream().flush() << "[DEBUG]" << Message_).str());
#define LOG_ERROR(Message_) Logger::Instance()->LogLine(static_cast<std::ostringstream&>(std::ostringstream().flush() << "[ERROR] " << Message_ << " " << __FUNCTION__ << "() " << __FILE__ << " line " << __LINE__ ).str());

#endif