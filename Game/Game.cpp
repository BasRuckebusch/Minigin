#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#endif
#include "Minigin.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "Utils.h"

using namespace dae;

void load()
{
	std::unique_ptr<SoundSystem> ss = std::make_unique<SDLSoundSystem>();
	ServiceLocator::RegisterSoundSystem(std::move(ss));

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Level loading

	std::vector<std::string> levelNames{ "level.bmp", "bombtest.bmp", "enemytest2.bmp", "enemytest.bmp" };
	LoadLevel(levelNames[0], &scene);
	dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F1, std::make_unique<dae::NextLevel>(&scene, levelNames));

	// Sound
	const std::string title = ResourceManager::GetInstance().GetFullFilePath("TitleScreen.mp3");
	const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());

	ServiceLocator::GetSoundSystem().Play(titleID, 50.f);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
