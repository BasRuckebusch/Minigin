#include "ServiceLocator.h"
std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::SSInstance{ std::make_unique<NullSoundSystem>() };