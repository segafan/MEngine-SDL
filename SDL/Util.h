#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

#include <SDL.h>

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