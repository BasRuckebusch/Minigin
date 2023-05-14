#include <memory>
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const soundID, const float) override {}
		soundID AddSound(const char*) override { return 0; }
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
