//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <sstream>
#include <cctype>

#include <SDL2/SDL.h>

//Check if C++11 is supported
#if _MSC_VER >= 1600 || __cplusplus > 199711L
#define CPP11_SUPPORT
#elif _MSC_VER < 1600 || __cplusplus <= 199711L
#endif

//If no C++11 Support add some
#ifndef CPP11_SUPPORT
#define nullptr 0
#endif

//Text To Number
#ifdef CPP11_SUPPORT

#include <string>

//TODO: Add more text to number types
inline int TextToNumber(std::string text)
{
	return std::stoi(text);
}

#else

inline int TextToNumber(const char* str)
{
	int val = 0;
	while (*str)
	{
		val = val * 10 + (*str++ - '0');
	}
	return val;
}

#endif


//Number To String
#ifdef CPP11_SUPPORT

#include <string>

inline std::string NumberToString(unsigned int num)
{
	return std::to_string(num);
}

inline std::string NumberToString(int num)
{
	return std::to_string(num);
}

inline std::string NumberToString(unsigned long num)
{
	return std::to_string(num);
}

inline std::string NumberToString(long num)
{
	return std::to_string(num);
}

inline std::string NumberToString(float num)
{
	return std::to_string(num);
}

inline std::string NumberToString(double num)
{
	return std::to_string(num);
}

inline std::string NumberToString(long double num)
{
	return std::to_string(num);
}

inline std::string NumberToString(unsigned long long num)
{
	return std::to_string(num);
}

inline std::string NumberToString(long long  num)
{
	return std::to_string(num);
}

#else

template <typename T>
inline std::string NumberToString(T num)
{
	std::ostringstream ostr;
	ostr << num;

	return ostr.str();
}

#endif

inline void SwapValues(int& a, int& b)
{
	if (a != b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
}

inline void SwapValues(float& a, float& b)
{
	if (a != b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
	}
}

inline std::vector<std::string> &SplitString(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

inline std::vector<std::string> SplitString(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	SplitString(s, delim, elems);
	return elems;
}

inline bool IsNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

inline std::string FormatRecv(const std::string& text)
{
	return text.substr(0, text.find_last_of('/'));	
}

inline bool ContainsFlag(int flags, int flag)
{
	return ((flags & flag) == flag);
}

inline std::string CreateString(std::string text1, std::string text2, std::string text3)
{
	std::string text = "";
	text += text1;
	text += text2;
	text += text3;

	return text;
}

inline char* CreateText(std::string text1, std::string text2, std::string text3)
{
	std::string stringText = CreateString(text1, text2, text3);

	std::vector<char> text;
	text.assign(stringText.begin(), stringText.end());
	text.push_back('\0');

	return &text[0];
}

inline SDL_Rect SetValues(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return rect;
}

#endif