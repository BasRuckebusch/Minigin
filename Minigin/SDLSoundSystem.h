#include <SDL_mixer.h>
#include <vector>

#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() = default;

		void Play(soundID id, float volume) override;
		soundID AddSound(const char* path) override;

	private:
		std::vector<Mix_Chunk*> m_Sounds;
	};
}

