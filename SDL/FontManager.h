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

#include <unordered_map>

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
	void AddFont(std::string filepath, unsigned int key, int size);
	void AddFont(TTF_Font* font, unsigned int key, int size);
	void RemoveFont(unsigned int key, int size);

	TTF_Font* GetFont(unsigned int key, int size);

	void Clear();

	//Draw Font
	//TODO: Add more Draw() options
	//TODO: Add every letter as a Texture and draw every letter of the text one by one
	//TDOD: Add align Center | Left |Right

	//Drawing with SDL_Rect

	void DrawText(unsigned int key, int size, std::string text, SDL_Rect *pos, SDL_Color color, int align);
	void DrawText(unsigned int key, int size, std::string text, SDL_Rect *pos, Color color, int align);

	//Drawing with own Rect

	void DrawText(unsigned int key, int size, std::string text, Rect *pos, SDL_Color color, int align);
	void DrawText(unsigned int key, int size, std::string text, Rect *pos, Color color, int align);
private:
	Camera& camera;

	std::unordered_map<unsigned int, std::unordered_map<int, TTF_Font*> > fonts;

	SDL_Window *window;
	SDL_Renderer *renderer;
};

#endif