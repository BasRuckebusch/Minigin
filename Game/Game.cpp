#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif
#include "CustomCommand.h"
#include "FPSComponent.h"
#include "Minigin.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
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

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	const std::string file{ dae::ResourceManager::GetInstance().GetFullFilePath("level1.bmp") };
	const glm::vec2 worldPos = { 208, 16 };
	LoadLevelFromBMP(file, &scene, worldPos, 16);

	auto go = std::make_shared<GameObject>();

	//	go->AddComponent<TextureComponent>("background.tga");
	//	scene.Add(go);
	//	
	//	go = std::make_shared<GameObject>();
	//	go->AddComponent<TextureComponent>("logo.tga");
	//	go->SetPosition(216, 180);
	//	scene.Add(go);
	//	
	//	go = std::make_shared<GameObject>();
	//	go->AddComponent<TextureComponent>();
	//	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	//	go->SetPosition(80, 20);
	//	scene.Add(go);

	const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->AddComponent<TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	go->AddComponent<FPSComponent>();
	go->SetPosition(0, 5);
	scene.Add(go);

	//const auto player2 = std::make_shared<GameObject>();
	//player2->SetLocalPosition(glm::vec3(256, 300, 0));
	//player2->AddComponent<TextureComponent>("enemy.tga");
	//player2->AddComponent<MoveComponent>();
	//scene.Add(player2);

	//const std::string title = ResourceManager::GetInstance().GetFullFilePath("TitleScreen.mp3");
	//const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());

	//ServiceLocator::GetSoundSystem().Play(titleID, 50.f);

	const auto player = std::make_shared<GameObject>();
	player->SetLocalPosition(glm::vec3(256, 62, 0));
	player->AddComponent<TextureComponent>("player.tga");
	player->AddComponent<MoveComponent>();
	player->AddComponent<PeterComponent>();
	//const auto coll = player->AddComponent<BoxColliderComponent>(player->GetWorldPosition(), 2, 5);
	//coll->SetOffset({ 2,14 });
	//const auto colr = player->AddComponent<BoxColliderComponent>(player->GetWorldPosition(), 2,5);
	//colr->SetOffset({12,14});
	scene.Add(player);

	auto& input = InputManager::GetInstance();

	input.BindCommand(ControllerButton::Left, std::make_unique<Move>(player.get(), glm::vec2{ -1.f, 0.f }), EventState::keyPressed);
	input.BindCommand(ControllerButton::Right, std::make_unique<Move>(player.get(), glm::vec2{ 1.f, 0.f }), EventState::keyPressed);
	input.BindCommand(ControllerButton::Up, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, -1.f }), EventState::keyPressed);
	input.BindCommand(ControllerButton::Down, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, 1.f }), EventState::keyPressed);

	input.BindCommand(SDLK_a, std::make_unique<Move>(player.get(), glm::vec2{ -1.f, 0.f }), EventState::keyPressed);
	input.BindCommand(SDLK_d, std::make_unique<Move>(player.get(), glm::vec2{ 1.f, 0.f }), EventState::keyPressed);
	input.BindCommand(SDLK_w, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, -1.f }), EventState::keyPressed);
	input.BindCommand(SDLK_s, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, 1.f }), EventState::keyPressed);
}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
