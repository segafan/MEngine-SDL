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
	Global(Display* display)
		: input()
		, display(*display)
		, state()
		, audio()
		, gfx()
	{
	}

	Input input;
	Display& display;
	StateManager state;
	AudioManager audio;
	GraphicsManager gfx;
};

#endif