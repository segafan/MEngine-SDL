//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "Display.h"
#include "Logger.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

class Global
{
public:
	Global(Display* display, Logger *logger)
		: input()
		, display(*display)
		, logger(*logger)
		, state()
		, audio(logger)
		, gfx(display->GetWindow(), display->GetRenderer(), logger)
	{
	}

	Input input;
	Display& display;
	Logger& logger;
	StateManager state;
	AudioManager audio;
	GraphicsManager gfx;
};

#endif