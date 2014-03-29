#ifndef DATA_H
#define DATA_H

#include "Input.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Data
{
public:
	Data(SDL_Window *window, SDL_Renderer *renderer)
	{
		input = new Input();
		audio = new AudioManager();
		gfx = new GraphicsManager(window, renderer);
	}
	
	~Data()
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