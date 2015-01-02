//========= Copyright Marcell Games, All rights reserved. ============//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Logger.h"

#ifdef CPP11_SUPPORT
#include <unordered_map>
#else
#include <map>
#endif

//TODO: Add RemoveMusic and SoundEffect
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	//Music
	void AddMusic(std::string filepath, std::string key);
	void RemoveMusic(std::string key);

	void PlayMusic(std::string key);
	void PlayMusic(std::string key, int loops);

	void StopMusic();

	void PauseMusic();
	
	void ResumeMusic();

	void MusicVolume(int volume);

	//SoundEffect

	void AddSoundEffect(std::string filepath, std::string key);
	void RemoveSoundEffect(std::string key);

	void PlaySoundEffect(std::string key);
	void PlaySoundEffect(std::string key, int loops);

	void SoundEffectVolume(std::string key, int volume);
	void SoundEffectsVolume(int volume);

	//Both
	void Stop();
	void Pause();
	void Resume();

	void Clear();
private:

#ifdef CPP11_SUPPORT
	std::unordered_map<std::string, Mix_Music*> music;
	std::unordered_map<std::string, Mix_Chunk*> soundEffect;
#else
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> soundEffect;
#endif
};

#endif