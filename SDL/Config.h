//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef CONFIG_H
#define CONFIG_H

//Define used Operating System
#if defined(_WIN64)
	#define OS_WINDOWS
	#define OS_WINDOWS_64
#elif defined(_WIN32)
	#define OS_WINDOWS
	#define OS_WINDOWS_32
#elif defined(__linux__) || defined(__linux)
	#define OS_LINUX
#elif defined(__unix__) || defined(__unix)
	#define OS_UNIX
#elif defined(__APPLE__) || defined(__MACH__)
	#include "TargetConditionals.h"
	#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
		#define OS_IOS
		#elif TARGET_OS_MAC
		#define OS_MAC
	#else
		#define OS_APPLE_UNKNOWN
	#endif
#elif defined(__ANDROID__) || defined(__ANDROID_API__) || defined(ANDROID) || defined(TARGET_OS_ANDROID)
	#define OS_ANDROID
#elif defined(__FreeBSD__)
	#define OS_FREEBSD
#elif  defined(__posix__) || defined(__posix)
	#define OS_POSIX
#else
	#define OS_OTHER
#endif

//Get if debug mode is used
//TODO: Needs some work to be cross platfrom
#if defined(_DEBUG)
	#define DEBUG_MODE
#endif

#endif