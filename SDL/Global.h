//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef GLOBAL_H
#define GLOBAL_H

#include "Input.h"
#include "Display.h"
#include "Logger.h"
#include "StateManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

#include "Camera.h"

class Global
{
public:
	Global(Display* display, Logger *logger)
		: camera()
		, input()
		, display(*display)
		, logger(*logger)
		, state()
		, audio(logger)
		, gfx(display, camera, logger)
	{
	}

	Camera camera;
	Input input;
	Display& display;
	Logger& logger;
	StateManager state;
	AudioManager audio;
	GraphicsManager gfx;
};

#endif