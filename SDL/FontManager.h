//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Util.h"
#include "Rect.h"
#include "Logger.h"
#include "Display.h"

#include "Camera.h"

//TOOD: This may create bugs & errors if it does redefine DrawText at the end of the file
#ifdef DrawText
#undef DrawText
#endif

#ifdef CPP11_SUPPORT
#include <unordered_map>
#else
#include <map>
#endif

enum Align
{
	ALIGN_NONE = 0,

	ALIGN_CENTER = 1,
	
	ALIGN_LEFT_X = 2,
	ALIGN_RIGHT_X = 4,
	ALIGN_CENTER_X = 8,

	ALIGN_UP_Y = 16,
	ALIGN_DOWN_Y = 32,
	ALIGN_CENTER_Y = 64
};

class FontManager
{
public:
	FontManager(Display* display);
	~FontManager();

	//Add & Destroy Fonts
	void AddFont(std::string filepath, std::string key, int size);
	void AddFont(TTF_Font* font, std::string key, int size);
	void RemoveFont(std::string key, int size);

	TTF_Font* GetFont(std::string key, int size);

	void Clear();

	//Draw Font
	//TODO: Add more Draw() options
	//TODO: Add every letter as a Texture and draw every letter of the text one by one
	//TDOD: Add align Center | Left |Right

	//Drawing with SDL_Rect

	void DrawText(std::string key, int size, std::string text, SDL_Rect *pos, SDL_Color color, int align);
	void DrawText(std::string key, int size, std::string text, SDL_Rect *pos, Color color, int align);

	//Drawing with own Rect

	void DrawText(std::string key, int size, std::string text, Rect *pos, SDL_Color color, int align);
	void DrawText(std::string key, int size, std::string text, Rect *pos, Color color, int align);
private:
	Camera& camera;

#ifdef CPP11_SUPPORT
	std::unordered_map<std::string, std::unordered_map<int, TTF_Font*> > fonts;

	std::unordered_map<std::string, std::unordered_map<int, bool> > errorShown;
#else
	std::map<std::string, std::map<int, TTF_Font*> > fonts;

	std::map<std::string, std::map<int, bool> > errorShown;
#endif

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif