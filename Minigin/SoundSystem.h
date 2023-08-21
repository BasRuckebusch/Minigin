#pragma once

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		
		virtual void PlaySound(int) {}
		virtual void StopSound(int ) {}
		virtual void StopEverySound() {}

		virtual void PlayMusic() {}
		virtual void TogglePauseMusic() {}

		virtual int LoadSound(const char* ) { return -1; }
		virtual void LoadMusic(const char* ) {}

		virtual void SetEffectVolume(int ) {}
		virtual void SetMusicVolume(int ) {}
	};
}
