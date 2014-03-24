#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <map>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

class AudioManager
{
public:
	AudioManager()
	{
		
	}
	~AudioManager()
	{
		Clear();
	}

	//Music
	void AddMusic(char* filepath, char* key)
	{
		if (music[key] != NULL)
		{
			//TODO: Log this
			std::cout << "There is already a music with that key! Key: " << key << std::endl;
			return;
		}

		Mix_Music* tempMusic = NULL;
		tempMusic = Mix_LoadMUS(filepath);

		if (tempMusic == NULL)
		{
			//TODO: Log this
			std::cout << "Music couldn't be loaded! Key: " << key << " Error: " << SDL_GetError() << std::endl;
			return;
		}

		music[key] = tempMusic;
	}

	inline void PlayMusic(char* key)
	{
		PlayMusic(key, -1);
	}
	inline void PlayMusic(char* key, int loops)
	{
		if (music[key] == NULL)
		{
			//TODO: Log this
			std::cout << "Music couldn't be played because it doesn't exist! Key: " << key << std::endl;
			return;
		}

		Mix_PlayMusic(music[key], loops);
	}

	void StopMusic()
	{
		Mix_HaltMusic();
	}

	void PauseMusic()
	{
		Mix_PauseMusic();
	}
	
	void ResumeMusic()
	{
		Mix_ResumeMusic();
	}

	void MusicVolume(int volume)
	{
		if (volume > 100)
			volume = 100;
		if (volume < 0)
			volume = 0;

		Mix_VolumeMusic((MIX_MAX_VOLUME / 100) * volume);
	}

	//SoundEffect

	void AddSoundEffect(char* filepath, char* key)
	{
		if (soundEffect[key] != NULL)
		{
			//TODO: Log this
			std::cout << "There is already a soundEffect with that key! Key: " << key << std::endl;
			return;
		}

		Mix_Chunk* tempEffect = NULL;
		tempEffect = Mix_LoadWAV(filepath);

		if (tempEffect == NULL)
		{
			//TODO: Log this
			std::cout << "SoundEffect couldn't be loaded! Key: " << key << " Error: " << SDL_GetError() << std::endl;
			return;
		}

		soundEffect[key] = tempEffect;
	}

	void PlaySoundEffect(char* key)
	{
		PlaySoundEffect(key, 0);
	}
	void PlaySoundEffect(char* key, int loops)
	{
		if (soundEffect[key] == NULL)
		{
			//TODO: Log this
			std::cout << "SoundEffect couldn't be played because it doesn't exist! Key: " << key << std::endl;
			return;
		}

		Mix_PlayChannel(-1, soundEffect[key], loops);
	}

	void SoundEffectVolume(char* key, int volume)
	{
		if (volume > 100)
			volume = 100;
		if (volume < 0)
			volume = 0;

		if (soundEffect[key] == NULL)
		{
			//TODO: Log this
			std::cout << "SoundEffect's volume couldn't be changed because it doesn't exist! Key: " << key << std::endl;
			return;
		}

		Mix_VolumeChunk(soundEffect[key], (MIX_MAX_VOLUME / 100) * volume);
	}
	void SoundEffectsVolume(int volume)
	{
		if (volume > 100)
			volume = 100;
		if (volume < 0)
			volume = 0;

		Mix_Volume(-1, (MIX_MAX_VOLUME / 100) * volume);
	}

	//Both
	void Stop()
	{
		Mix_HaltChannel(-1);
	}
	void Pause()
	{
		Mix_Pause(-1);
	}
	void Resume()
	{
		Mix_Resume(-1);
	}

	void Clear()
	{
		Mix_HaltMusic();
		Mix_HaltChannel(-1);

		typedef std::map<std::string, Mix_Music*>::iterator it_type_music;

		for (it_type_music iterator = music.begin(); iterator != music.end(); iterator++)
		{
			if (music[iterator->first])
			{
				std::cout << "Destroyed music: " << iterator->first << std::endl;
				Mix_FreeMusic(music[iterator->first]);
			}
		}

		music.clear();

		typedef std::map<std::string, Mix_Chunk*>::iterator it_type_effect;

		for (it_type_effect iterator = soundEffect.begin(); iterator != soundEffect.end(); iterator++)
		{
			if (soundEffect[iterator->first])
			{
				std::cout << "Destroyed soundEffect: " << iterator->first << std::endl;
				Mix_FreeChunk(soundEffect[iterator->first]);
			}
		}

		soundEffect.clear();
	}
private:
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> soundEffect;
};

#endif