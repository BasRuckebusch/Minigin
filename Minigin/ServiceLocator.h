#include <memory>
#include "SoundSystem.h"

namespace dae
{
    class NullSoundSystem final : public SoundSystem
    {
    public:

        void PlaySound(int ) override {}
        void StopSound(int ) override {}
        void StopEverySound() override {}

        void PlayMusic() override {}
        void TogglePauseMusic() override {}

        int LoadSound(const char* ) override { return -1; }
        void LoadMusic(const char* ) override {}

        void SetEffectVolume(int ) override {}
        void SetMusicVolume(int) override {}
    };

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *SSInstance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss) { SSInstance = std::move(ss); }
	private:
		static std::unique_ptr<SoundSystem> SSInstance;
	};
}
