#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "Screen.h"
#include "Logger.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Global
{
public:
	Global(SDL_Window *window, SDL_Renderer *renderer, Logger *logger)
	{
		this->logger = logger;
		screen = new Screen(window, renderer);
		input = new Input();
		audio = new AudioManager(logger);
		gfx = new GraphicsManager(window, renderer, logger);
	}
	
	~Global()
	{
		delete screen;
		delete input;
		delete audio;
		delete gfx;
	}

	Input* input;
	Screen* screen;
	Logger* logger;
	AudioManager* audio;
	GraphicsManager* gfx;
};

#endif