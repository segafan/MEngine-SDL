#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "Screen.h"
#include "Logger.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Global
{
public:
	Global(SDL_Window *window, SDL_Renderer *renderer, Logger *logger)
		: input()
		, screen(window, renderer)
		, logger(*logger)
		, state()
		, audio(logger)
		, gfx(window, renderer, logger)
	{
	}

	Input input;
	WindowScreen screen;
	Logger& logger;
	StateManager state;
	AudioManager audio;
	GraphicsManager gfx;
};

#endif