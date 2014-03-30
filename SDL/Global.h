#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Global
{
public:
	Global(SDL_Window *window, SDL_Renderer *renderer)
	{
		input = new Input();
		audio = new AudioManager();
		gfx = new GraphicsManager(window, renderer);
	}
	
	~Global()
	{
		delete input;
		delete audio;
		delete gfx;
	}

	Input* input;
	AudioManager* audio;
	GraphicsManager* gfx;
};

#endif