#pragma once
namespace dae
{
	using soundID = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(soundID id, float volume) = 0;
		virtual soundID AddSound(const char* path) = 0;
	};
}
