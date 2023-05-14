#include "SDLSoundSystem.h"
#include <iostream>
#include <SDL_mixer.h>

dae::SDLSoundSystem::SDLSoundSystem()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		std::cerr << "Error in SDLSoundSystem: " << Mix_GetError() << std::endl;
	}
}

void dae::SDLSoundSystem::Play(soundID id, float volume)
{
	Mix_Chunk* pMixChunk = m_Sounds[id];
	pMixChunk->volume = static_cast<Uint8>(volume);
	Mix_PlayChannel(-1, pMixChunk, 0);
}

dae::soundID dae::SDLSoundSystem::AddSound(const char* path)
{
	Mix_Chunk* pMixChunk = Mix_LoadWAV(path);
	m_Sounds.push_back(pMixChunk);
	return static_cast<soundID>(m_Sounds.size()) - 1;
}
