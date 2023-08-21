#include "SDLSoundSystem.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

namespace dae
{
	SDLSoundSystemImpl::SDLSoundSystemImpl()
		: m_pMusic(nullptr), m_Running(true)
	{
		if (SDL_Init(SDL_INIT_AUDIO) == -1)
		{
			std::cerr << "Error in SDL_Init: " << SDL_GetError() << std::endl;
			exit(1);
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			std::cerr << "Error in Mix_OpenAudio: " << Mix_GetError() << std::endl;
			exit(2);
		}

		m_AudioThread = std::thread(&SDLSoundSystemImpl::AudioThreadFunction, this);
	}

	SDLSoundSystemImpl::~SDLSoundSystemImpl()
	{
		m_Running = false;
		m_ConditionVariable.notify_one();
		m_AudioThread.join();

		for (Mix_Chunk* chunk : m_pSounds)
			Mix_FreeChunk(chunk);

		if (m_pMusic)
			Mix_FreeMusic(m_pMusic);

		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
	}

	void SDLSoundSystemImpl::PlaySound(int soundID)
	{
		std::lock_guard lock(m_Mutex);
		m_SoundQueue.push(soundID);
		m_ConditionVariable.notify_one();
	}

	void SDLSoundSystemImpl::StopSound(int channelId)
	{
		Mix_HaltChannel(channelId);
	}

	void SDLSoundSystemImpl::StopEverySound()
	{
		Mix_HaltChannel(-1);
		Mix_HaltMusic();
		m_Running = false;
		m_ConditionVariable.notify_one();
	}

	void SDLSoundSystemImpl::PlayMusic() const
	{
		Mix_PlayMusic(m_pMusic, -1);
	}

	void SDLSoundSystemImpl::TogglePauseMusic()
	{
		if (m_Paused)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
		m_Paused = !m_Paused;
	}

	int SDLSoundSystemImpl::LoadSound(const char* file)
	{
		if (Mix_Chunk* sound = Mix_LoadWAV(file))
		{
			m_pSounds.push_back(sound);
			return static_cast<int>(m_pSounds.size()) - 1;
		}
		return -1;
	}

	void SDLSoundSystemImpl::LoadMusic(const char* file)
	{
		m_pMusic = Mix_LoadMUS(file);
	}

	void SDLSoundSystemImpl::SetEffectVolume(int volume)
	{
		Mix_Volume(-1, volume);
	}

	void SDLSoundSystemImpl::SetMusicVolume(int volume)
	{
		Mix_VolumeMusic(volume);
	}

	void SDLSoundSystemImpl::AudioThreadFunction()
	{
		while (m_Running)
		{
			std::unique_lock lock(m_Mutex);
			m_ConditionVariable.wait(lock, [&] { return !m_SoundQueue.empty() || !m_Running; });
			lock.unlock();

			// Process sounds while holding the lock is no longer necessary
			ProcessSoundQueue();
		}
	}

	void SDLSoundSystemImpl::ProcessSoundQueue()
	{
		std::queue<int> soundsToPlay;
		{
			std::lock_guard lock(m_Mutex);

			// Move the sound IDs to a local queue for processing
			std::swap(soundsToPlay, m_SoundQueue);
		}

		// Process each sound in the local queue
		while (!soundsToPlay.empty())
		{
			const int id = soundsToPlay.front();
			soundsToPlay.pop();

			// Ensure the sound ID is within valid range
			if (id >= 0 && id < static_cast<int>(m_pSounds.size()))
			{
				Mix_PlayChannel(-1, m_pSounds[id], 0);
			}
		}
	}

	SDLSoundSystem::SDLSoundSystem()
		: m_pImpl(std::make_unique<SDLSoundSystemImpl>())
	{
	}

	int SDLSoundSystem::LoadSound(const char* file)
	{
		return m_pImpl->LoadSound(file);
	}

	void SDLSoundSystem::LoadMusic(const char* file)
	{
		m_pImpl->LoadMusic(file);
	}

	void SDLSoundSystem::PlaySound(int soundID)
	{
		m_pImpl->PlaySound(soundID);
	}

	void SDLSoundSystem::StopSound(int channelId)
	{
		m_pImpl->StopSound(channelId);
	}

	void SDLSoundSystem::StopEverySound()
	{
		m_pImpl->StopEverySound();
	}

	void SDLSoundSystem::PlayMusic()
	{
		m_pImpl->PlayMusic();
	}

	void SDLSoundSystem::TogglePauseMusic()
	{
		m_pImpl->TogglePauseMusic();
	}

	void SDLSoundSystem::SetEffectVolume(int volume)
	{
		m_pImpl->SetEffectVolume(volume);
	}

	void SDLSoundSystem::SetMusicVolume(int volume)
	{
		m_pImpl->SetMusicVolume(volume);
	}
}