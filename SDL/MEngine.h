#ifndef MENGINE_H
#define MENGINE_H

//Check if NULL is defined
#ifndef NULL
#define NULL 0
#endif

//Check if C++11 is supported
#if _MSC_VER >= 1600 || __cplusplus > 199711L
#define cplusplus11 true
#elif _MSC_VER < 1600 || __cplusplus <= 199711L
#define cplusplus11 false
//Define C++11 stuff
#define nullptr NULL
#endif

#define GetArraySizeInElements(a) (sizeof(a)/sizeof(a[0]))

//C & C++
#include <iostream>

//SDL
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

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

#endif