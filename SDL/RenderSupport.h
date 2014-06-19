#ifndef RENDERSUPPORT_H
#define RENDERSUPPORT_H

#include <SDL2/SDL.h>

#include <vector>

#include "Logger.h"

inline bool GetRenderFlagAvailable(SDL_RendererInfo *info, unsigned int flag)
{
	return ((info->flags & flag) == flag);
}

inline bool GetRenderFlagAvailable(int num, int flag)
{
	SDL_RendererInfo info;
	if(SDL_GetRenderDriverInfo(num, &info) == 0)
		return GetRenderFlagAvailable(&info, flag);
	else
	{
		std::cout << "Can't Get Renderer Flag in GetRenderFlagAvailable(int num,int flag)! Error:" << SDL_GetError() << std::endl;
		return false;
	}
}

inline bool GetRenderFlagAvailable(SDL_Renderer *renderer, int flag)
{
	SDL_RendererInfo info;
	if (SDL_GetRendererInfo(renderer, &info) == 0)
		return GetRenderFlagAvailable(&info, flag);
	else
	{
		std::cout << "Can't Get Renderer Flag in GetRenderFlagAvailable(SDL_Renderer *renderer,int flag)! Error:" << SDL_GetError() << std::endl;
		return false;
	}
}


static Uint32 GetRenderFlags(SDL_Window *window, bool TargetTextureSupport, bool HaveVSYNC)
{
	Uint32 finalFlags = 0;
	
	bool textureTargetAvailable = false;

	bool hardwareTextureTarget = false;

	std::vector<bool> hardwareBool;
	std::vector<bool> softwareBool;
	std::vector<bool> textureBool;
	std::vector<bool> vsyncBool;

	std::vector<int> hardwareFlag;
	std::vector<int> softwareFlag;
	std::vector<int> textureFlag;
	std::vector<int> vsyncFlag;

	//Get Data
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
	{
		//Local Variable Create
		bool hardware = false;
		bool software = false;
		bool texture  = false;
		bool vsync   = false;

		int hardwareRender = 0;
		int softwareRender = 0;
		int targetTexture  = 0;
		int presentVSYNC   = 0;


		//Calculate
		SDL_RendererInfo info;
		SDL_GetRenderDriverInfo(i, &info);


		hardware = GetRenderFlagAvailable(&info, SDL_RENDERER_ACCELERATED);
		software = GetRenderFlagAvailable(&info, SDL_RENDERER_SOFTWARE);
		texture = GetRenderFlagAvailable(&info, SDL_RENDERER_TARGETTEXTURE);
		vsync = GetRenderFlagAvailable(&info, SDL_RENDERER_PRESENTVSYNC);


		if (hardware)
			hardwareRender = SDL_RENDERER_ACCELERATED;
		if(software)
			softwareRender = SDL_RENDERER_SOFTWARE;
		if (texture)
			targetTexture = SDL_RENDERER_TARGETTEXTURE;
		if (vsync && HaveVSYNC)
			presentVSYNC = SDL_RENDERER_PRESENTVSYNC;


		if (TargetTextureSupport && texture)
			textureTargetAvailable = true;

		//Push To Global
		hardwareBool.push_back(hardware);
		softwareBool.push_back(software);
		textureBool.push_back(texture);
		vsyncBool.push_back(vsync);

		hardwareFlag.push_back(hardwareRender);
		softwareFlag.push_back(softwareRender);
		textureFlag.push_back(targetTexture);
		vsyncFlag.push_back(presentVSYNC);
	}
	
	//Use Data To Get Hardware Acceleration
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
	{
		if (hardwareBool[i])
		{
			if (vsyncBool[i] && textureBool[i])
			{
				finalFlags = (hardwareFlag[i] | textureFlag[i] | vsyncFlag[i]);
				hardwareTextureTarget = true;
				break;
			}
			else if (textureBool[i])
			{
				finalFlags = (hardwareFlag[i] | textureFlag[i]);
				hardwareTextureTarget = true;
				break;
			}
			else if (vsyncBool[i])
			{
				finalFlags = (hardwareFlag[i] | vsyncFlag[i]);
				break;
			}
			else
			{
				finalFlags = (hardwareFlag[i]);
				break;
			}
		}
	}

	//Software Acceleration (if no TargetTexture or no Hardware)
	if ((finalFlags == 0) || (TargetTextureSupport && !hardwareTextureTarget && textureTargetAvailable))
	{
		for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
		{
			if (softwareBool[i])
			{
				if (vsyncBool[i] && textureBool[i])
				{
					finalFlags = (softwareFlag[i] | textureFlag[i] | vsyncFlag[i]);
					break;
				}
				else if (textureBool[i])
				{
					finalFlags = (softwareFlag[i] | textureFlag[i]);
					break;
				}
				else if (vsyncBool[i])
				{
					finalFlags = (softwareFlag[i] | vsyncFlag[i]);
					break;
				}
				else
				{
					finalFlags = (softwareFlag[i]);
					break;
				}
			}
		}
	}
	
	//Final Error Checks
	if (finalFlags == 0)
	{
		SDL_ShowSimpleMessageBox(0, "Error", "No Hardware or Software Acceleration Available! ", window);
		std::cout << "No Hardware or Software Acceleration Available! Error: " << SDL_GetError() << std::endl;
	}

	if (!textureTargetAvailable && TargetTextureSupport)
	{
		SDL_ShowSimpleMessageBox(0, "Error", "Error your videocard doesn't support TargetTexture! \n IT MAY CAUSE PROGRAM CRASHES!", window);
		std::cout << "Error your videocard doesn't support TargetTexture! Error: " << SDL_GetError() << std::endl;
	}

	//Clear Memory
	
	hardwareBool.clear();
	softwareBool.clear();
	textureBool.clear();
	vsyncBool.clear();

	hardwareFlag.clear();
	softwareFlag.clear();
	textureFlag.clear();
	vsyncFlag.clear();

	return finalFlags;
}

//Print

static void PrintRenderFlags(Uint32 flags)
{
	std::cout << "Used Render Flags:" << std::endl;

	if ((flags & SDL_RENDERER_SOFTWARE) == SDL_RENDERER_SOFTWARE)
		std::cout << "		" << "SDL_RENDERER_SOFTWARE" << "		   [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_SOFTWARE" << "		   [ ]" << std::endl;

	if ((flags & SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED)
		std::cout << "		" << "SDL_RENDERER_ACCELERATED" << "	   [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_ACCELERATED" << "	   [ ]" << std::endl;

	if ((flags & SDL_RENDERER_TARGETTEXTURE) == SDL_RENDERER_TARGETTEXTURE)
		std::cout << "		" << "SDL_RENDERER_TARGETTEXTURE" << "	   [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_TARGETTEXTURE" << "	   [ ]" << std::endl;

	if ((flags & SDL_RENDERER_PRESENTVSYNC) == SDL_RENDERER_PRESENTVSYNC)
		std::cout << "		" << "SDL_RENDERER_PRESENTVSYNC" << "	   [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_PRESENTVSYNC" << "	   [ ]" << std::endl;
}

static void PrintRenderInfo(SDL_RendererInfo* info)
{
	std::cout << "- " << info->name << std::endl;

	if (GetRenderFlagAvailable(info, SDL_RENDERER_SOFTWARE))
		std::cout << "		" << "SDL_RENDERER_SOFTWARE " << "	   [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_SOFTWARE " << "	   [ ]" << std::endl;

	if (GetRenderFlagAvailable(info, SDL_RENDERER_ACCELERATED))
		std::cout << "		" << "SDL_RENDERER_ACCELERATED " << "  [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_ACCELERATED " << "  [ ]" << std::endl;

	if (GetRenderFlagAvailable(info, SDL_RENDERER_PRESENTVSYNC))
		std::cout << "		" << "SDL_RENDERER_PRESENTVSYNC " << " [X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_PRESENTVSYNC " << " [ ]" << std::endl;

	if (GetRenderFlagAvailable(info, SDL_RENDERER_TARGETTEXTURE))
		std::cout << "		" << "SDL_RENDERER_TARGETTEXTURE " << "[X]" << std::endl;
	else
		std::cout << "		" << "SDL_RENDERER_TARGETTEXTURE " << "[ ]" << std::endl;
}

inline void GetRenderInfo(int num)
{
	SDL_RendererInfo info;
	SDL_GetRenderDriverInfo(num, &info);
	
	PrintRenderInfo(&info);
}

static void GetAllRenderInfo()
{
	std::cout << "Available Render Drivers:" << std::endl;
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
	{
		GetRenderInfo(i);
	}
	std::cout << std::endl;
}

inline void GetUsedRenderInfo(SDL_Renderer *renderer)
{
	std::cout << "Used Render Driver:" << std::endl;
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer, &info);

	PrintRenderInfo(&info);
}

//Log

static void LogRenderFlags(Uint32 flags, Logger *logger)
{
	logger->LogLineWithoutTime("Used Render Flags:");

	if ((flags & SDL_RENDERER_SOFTWARE) == SDL_RENDERER_SOFTWARE)
		logger->LogLineWithoutTime("		", "SOFTWARE");

	if ((flags & SDL_RENDERER_ACCELERATED) == SDL_RENDERER_ACCELERATED)
		logger->LogLineWithoutTime("		", "ACCELERATED");

	if ((flags & SDL_RENDERER_TARGETTEXTURE) == SDL_RENDERER_TARGETTEXTURE)
		logger->LogLineWithoutTime("		", "TARGETTEXTURE");

	if ((flags & SDL_RENDERER_PRESENTVSYNC) == SDL_RENDERER_PRESENTVSYNC)
		logger->LogLineWithoutTime("		", "PRESENTVSYNC");

	logger->NewLine();
}

static void LogRenderInfo(SDL_RendererInfo* info, Logger *logger)
{
	logger->LogLineWithoutTime("- ",info->name);

	if (GetRenderFlagAvailable(info, SDL_RENDERER_SOFTWARE))
		logger->LogLineWithoutTime("		","SOFTWARE");

	if (GetRenderFlagAvailable(info, SDL_RENDERER_ACCELERATED))
		logger->LogLineWithoutTime("		", "ACCELERATED");

	if (GetRenderFlagAvailable(info, SDL_RENDERER_PRESENTVSYNC))
		logger->LogLineWithoutTime("		", "PRESENTVSYNC");

	if (GetRenderFlagAvailable(info, SDL_RENDERER_TARGETTEXTURE))
		logger->LogLineWithoutTime("		", "TARGETTEXTURE");
}

static void LogRenderInfo(int num, Logger *logger)
{
	SDL_RendererInfo info;
	SDL_GetRenderDriverInfo(num, &info);

	LogRenderInfo(&info,logger);
}

static void LogAllRenderInfo(Logger *logger)
{
	logger->LogLineWithoutTime("Available Render Drivers:");
	for (int i = 0; i < SDL_GetNumRenderDrivers(); i++)
	{
		LogRenderInfo(i,logger);
	}
	logger->NewLine();
}

static void LogUsedRenderInfo(SDL_Renderer *renderer, Logger *logger)
{
	logger->LogLineWithoutTime("Used Render Driver:");
	SDL_RendererInfo info;
	SDL_GetRendererInfo(renderer, &info);

	LogRenderInfo(&info,logger);

	logger->NewLine();
}

#endif