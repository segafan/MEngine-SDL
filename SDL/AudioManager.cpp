#include "AudioManager.h"

AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{
	Clear();
}

void AudioManager::AddMusic(std::string filepath, std::string key)
{
	if (music[key] != NULL)
	{
		LOG_DEBUG("There is already a music with that key! Key: " << key);
		return;
	}

	Mix_Music* tempMusic = NULL;
	tempMusic = Mix_LoadMUS(filepath.c_str());

	if (tempMusic == NULL)
	{
		LOG_ERROR("Music couldn't be loaded! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	music[key] = tempMusic;
}

void AudioManager::RemoveMusic(std::string key)
{
	if (music[key] == NULL)
	{
		LOG_DEBUG("The music can't be removed because it doesn't exist! Key: " << key);
		return;
	}

	Mix_FreeMusic(music[key]);
	music[key] = NULL;
}

void AudioManager::PlayMusic(std::string key)
{
	PlayMusic(key, -1);
}

void AudioManager::PlayMusic(std::string key, int loops)
{
	if (music[key] == NULL)
	{
		LOG_ERROR("Music couldn't be played because it doesn't exist! Key: " << key);
		return;
	}

	Mix_PlayMusic(music[key], loops);
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

void AudioManager::MusicVolume(int volume)
{
	if (volume > 100)
		volume = 100;
	if (volume < 0)
		volume = 0;

	Mix_VolumeMusic((MIX_MAX_VOLUME / 100) * volume);
}

void AudioManager::AddSoundEffect(std::string filepath, std::string key)
{
	if (soundEffect[key] != NULL)
	{
		LOG_DEBUG("There is already a soundEffect with that key! Key: " << key);
		return;
	}

	Mix_Chunk* tempEffect = NULL;
	tempEffect = Mix_LoadWAV(filepath.c_str());

	if (tempEffect == NULL)
	{
		LOG_ERROR("SoundEffect couldn't be loaded! Key: " << key << " Error: " << SDL_GetError());
		return;
	}

	soundEffect[key] = tempEffect;
}

void AudioManager::RemoveSoundEffect(std::string key)
{
	if (soundEffect[key] == NULL)
	{
		LOG_DEBUG("The SoundEffect can't be removed because it doesn't exist! Key: " << key);
		return;
	}

	Mix_FreeChunk(soundEffect[key]);
	soundEffect[key] = NULL;
}

void AudioManager::PlaySoundEffect(std::string key)
{
	PlaySoundEffect(key, 0);
}

void AudioManager::PlaySoundEffect(std::string key, int loops)
{
	if (soundEffect[key] == NULL)
	{
		LOG_ERROR("SoundEffect couldn't be played because it doesn't exist! Key: " << key);
		return;
	}

	Mix_PlayChannel(-1, soundEffect[key], loops);
}

void AudioManager::SoundEffectVolume(std::string key, int volume)
{
	if (volume > 100)
		volume = 100;
	if (volume < 0)
		volume = 0;

	if (soundEffect[key] == NULL)
	{
		LOG_DEBUG("SoundEffect's volume couldn't be changed because it doesn't exist! Key: " << key);
		return;
	}

	Mix_VolumeChunk(soundEffect[key], (MIX_MAX_VOLUME / 100) * volume);
}

void AudioManager::SoundEffectsVolume(int volume)
{
	if (volume > 100)
		volume = 100;
	if (volume < 0)
		volume = 0;

	Mix_Volume(-1, (MIX_MAX_VOLUME / 100) * volume);
}

void AudioManager::Stop()
{
	Mix_HaltChannel(-1);
}

void AudioManager::Pause()
{
	Mix_Pause(-1);
}

void AudioManager::Resume()
{
	Mix_Resume(-1);
}

void AudioManager::Clear()
{
	Mix_HaltMusic();
	Mix_HaltChannel(-1);
#ifdef CPP11_SUPPORT
	typedef std::unordered_map<std::string, Mix_Music*>::iterator it_type_music;
#else
	typedef std::map<std::string, Mix_Music*>::iterator it_type_music;
#endif
	for (it_type_music iterator = music.begin(); iterator != music.end(); iterator++)
	{
		if (music[iterator->first] != NULL)
		{
			std::cout << "Destroyed music: " << iterator->first << std::endl;
			Mix_FreeMusic(music[iterator->first]);
			music[iterator->first] = NULL;
		}
	}

	music.clear();
#ifdef CPP11_SUPPORT
	typedef std::unordered_map<std::string, Mix_Chunk*>::iterator it_type_effect;
#else
	typedef std::map<std::string, Mix_Chunk*>::iterator it_type_effect;
#endif
	for (it_type_effect iterator = soundEffect.begin(); iterator != soundEffect.end(); iterator++)
	{
		if (soundEffect[iterator->first] != NULL)
		{
			std::cout << "Destroyed soundEffect: " << iterator->first << std::endl;
			Mix_FreeChunk(soundEffect[iterator->first]);
			soundEffect[iterator->first] = NULL;
		}
	}

	soundEffect.clear();
}
