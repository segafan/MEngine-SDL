#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "Logger.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Global
{
public:
	Global(SDL_Window *window, SDL_Renderer *renderer, Logger *logger)
	{
		this->logger = logger;
		input = new Input();
		audio = new AudioManager(logger);
		gfx = new GraphicsManager(window, renderer, logger);
	}
	
	~Global()
	{
		delete input;
		delete audio;
		delete gfx;
	}

	Input* input;
	Logger* logger;
	AudioManager* audio;
	GraphicsManager* gfx;
};

#endif