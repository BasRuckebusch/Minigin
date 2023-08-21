#include <SDL_mixer.h>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <iostream>
#include <queue>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystemImpl
	{
	public:
		SDLSoundSystemImpl();
		~SDLSoundSystemImpl();

		int LoadSound(const char* file);
		void LoadMusic(const char* file);

		void PlaySound(int soundID);
		static void StopSound(int channelId);
		void StopEverySound();

		void PlayMusic() const;
		void TogglePauseMusic();

		static void SetEffectVolume(int volume);
		static void SetMusicVolume(int volume);

	private:
		void AudioThreadFunction();
		void ProcessSoundQueue();

		std::vector<Mix_Chunk*> m_pSounds;
		Mix_Music* m_pMusic;

		std::queue<int> m_SoundQueue;
		std::mutex m_Mutex;
		std::condition_variable m_ConditionVariable;

		bool m_Running;
		bool m_Paused;
		std::thread m_AudioThread;
	};

	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override = default;

		int LoadSound(const char* file) override;
		void LoadMusic(const char* file) override;

		void PlaySound(int soundID) override;
		void StopSound(int channelId) override;
		void StopEverySound() override;

		void PlayMusic() override;
		void TogglePauseMusic() override;

		void SetEffectVolume(int volume) override;
		void SetMusicVolume(int volume) override;

	private:
		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}