//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef MENGINE_H
#define MENGINE_H

//Define NULL
#ifndef NULL
#define NULL 0
#endif

//Define null
#ifndef null
#define null 0
#endif

#define GetArraySizeInElements(a) (sizeof(a)/sizeof(a[0]))

//C & C++
#include <iostream>

//SDL
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

//Basic System
#include "System.h"

//Logging
#include "Logger.h"

//Timing
#include "Timer.h"
#include "FPSTimer.h"

//Managers
#include "Global.h"
#include "AudioManager.h"
#include "GraphicsManager.h"

//Input
#include "Input.h"

//Positions
#include "Rect.h"
#include "Point.h"
#include "Vertex.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Quaternion.h"

//Random
#include "Random.h"

//Profiler
#include "Profiler.h"

#endif