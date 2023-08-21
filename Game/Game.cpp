#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//#include <vld.h>
#endif
#include "CustomCommand.h"
#include "EndComponent.h"
#include "Minigin.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SDLSoundSystem.h"
#include "SoundSystem.h"
#include "Utils.h"
#include "Gamepad.h"
#include "MoveComponent.h"
#include "PeterComponent.h"
#include "TextComponent.h"

using namespace dae;

//	void load()
//	{
//		std::unique_ptr<SoundSystem> ss = std::make_unique<SDLSoundSystem>();
//		ServiceLocator::RegisterSoundSystem(std::move(ss));
//	
//		auto& scene = SceneManager::GetInstance().CreateScene("Demo");
//		const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
//	
//		// Level loading
//	
//		std::vector<std::string> levelNames{"level.bmp", "level5.bmp", "level2.bmp", "level3.bmp","level6.bmp", "level4.bmp" };
//		LoadLevel(levelNames[0], &scene);
//		dae::InputManager::GetInstance().BindCommand(SDL_SCANCODE_F1, std::make_unique<dae::NextLevel>(&scene, levelNames));
//	
//		// Sound
//		const std::string title = ResourceManager::GetInstance().GetFullFilePath("TitleScreen.mp3");
//		const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());
//	
//		ServiceLocator::GetSoundSystem().Play(titleID, 50.f);
//	}

void load()
{
	std::unique_ptr<SoundSystem> ss = std::make_unique<SDLSoundSystem>();
	ServiceLocator::RegisterSoundSystem(std::move(ss));

	const std::string title = dae::ResourceManager::GetInstance().GetFullFilePath("TitleScreen.mp3");
	ServiceLocator::GetSoundSystem().LoadMusic(title.c_str());
	ServiceLocator::GetSoundSystem().PlayMusic();

	const std::string beep = dae::ResourceManager::GetInstance().GetFullFilePath("Beep.wav");
	ServiceLocator::GetSoundSystem().LoadSound(beep.c_str());
	const std::string fall = dae::ResourceManager::GetInstance().GetFullFilePath("Fall.wav");
	ServiceLocator::GetSoundSystem().LoadSound(fall.c_str());
	//ServiceLocator::GetSoundSystem().SetEffectVolume()

	auto& scene = SceneManager::GetInstance().CreateScene("Level1");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	std::vector<std::string> levelNames{ "level1.bmp", "level2.bmp", "level3.bmp" };
	LoadMenu(levelNames[0], &scene);
	auto& input = InputManager::GetInstance();
	input.BindCommand(SDLK_F1, std::make_unique<NextLevel>(&scene, levelNames), EventState::keyUp);
	input.BindCommand(SDLK_ESCAPE, std::make_unique<MenuLoad>(&scene, levelNames[0]), EventState::keyUp);
	input.BindCommand(SDLK_F2, std::make_unique<StopSound>(), EventState::keyUp);

	auto& scene2 = SceneManager::GetInstance().CreateScene("Extra");

	const auto go = std::make_shared<GameObject>();
	go->AddComponent<EndComponent>(&scene, levelNames);
	scene2.Add(go);

}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
