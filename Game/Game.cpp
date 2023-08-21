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

	auto& scene = SceneManager::GetInstance().CreateScene("Level1");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	std::vector<std::string> levelNames{ "level1.bmp", "level2.bmp", "level3.bmp" };
	LoadMenu(levelNames[0], &scene);
	auto& input = InputManager::GetInstance();
	input.BindCommand(SDLK_F1, std::make_unique<NextLevel>(&scene, levelNames), EventState::keyUp);
	input.BindCommand(SDLK_ESCAPE, std::make_unique<MenuLoad>(&scene, levelNames[0]), EventState::keyUp);

	auto& scene2 = SceneManager::GetInstance().CreateScene("Extra");

	const auto go = std::make_shared<GameObject>();
	go->AddComponent<EndComponent>(&scene, levelNames);
	scene2.Add(go);

	//auto go = std::make_shared<GameObject>();
	//const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	//go = std::make_shared<GameObject>();
	//go->AddComponent<TextureComponent>();
	//go->AddComponent<TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	//go->AddComponent<FPSComponent>();
	//go->SetPosition(0, 5);
	//scene2.Add(go);


	//	const int tileSize{ 16 };
	//	const int halfTileSize{ static_cast<int>(tileSize * .5f) };
	//	const glm::vec2 worldPos = { tileSize, tileSize };
	//	
	//	const std::string file1{ResourceManager::GetInstance().GetFullFilePath("level1.bmp") };
	//	LoadLevelFromBMP(file1, &scene1, worldPos, tileSize);
	//	//const std::string file2{ResourceManager::GetInstance().GetFullFilePath("level2.bmp") };
	//	//LoadLevelFromBMP(file2, &scene2, worldPos,tileSize);
	//	//const std::string file3{ResourceManager::GetInstance().GetFullFilePath("level3.bmp") };
	//	//LoadLevelFromBMP(file3, &scene3, worldPos,tileSize);
	//	
	//	const std::string ingredient1{ResourceManager::GetInstance().GetFullFilePath("ingredients1.bmp") };
	//	LoadIngredientsFromBMP(ingredient1, &scene1, worldPos, halfTileSize);
	//	//const std::string ingredient2{ResourceManager::GetInstance().GetFullFilePath("ingredients2.bmp") };
	//	//LoadIngredientsFromBMP(ingredient2, &scene2, worldPos, halfTileSize);
	//	//const std::string ingredient3{ResourceManager::GetInstance().GetFullFilePath("ingredients3.bmp") };
	//	//LoadIngredientsFromBMP(ingredient3, &scene3, worldPos, halfTileSize);

	//auto go = std::make_shared<GameObject>();

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

	//	const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	//	go = std::make_shared<GameObject>();
	//	go->AddComponent<TextureComponent>();
	//	go->AddComponent<TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	//	go->AddComponent<FPSComponent>();
	//	go->SetPosition(0, 5);
	//	scene1.Add(go);

	//const auto player2 = std::make_shared<GameObject>();
	//player2->SetLocalPosition(glm::vec3(256, 300, 0));
	//player2->AddComponent<TextureComponent>("enemy.tga");
	//player2->AddComponent<MoveComponent>();
	//scene.Add(player2);

	//const std::string title = ResourceManager::GetInstance().GetFullFilePath("TitleScreen.mp3");
	//const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());
	//ServiceLocator::GetSoundSystem().Play(titleID, 50.f);

	//	const auto player = std::make_shared<GameObject>();
	//	player->SetLocalPosition(glm::vec3(104, 62, 0));
	//	player->AddComponent<TextureComponent>("player.tga");
	//	player->AddComponent<MoveComponent>();
	//	player->AddComponent<PeterComponent>();
	//	scene.Add(player);
	//	
	//	//auto& input = InputManager::GetInstance();
	//	
	//	input.BindCommand(ControllerButton::Left, std::make_unique<Move>(player.get(), glm::vec2{ -1.f, 0.f }), EventState::keyPressed);
	//	input.BindCommand(ControllerButton::Right, std::make_unique<Move>(player.get(), glm::vec2{ 1.f, 0.f }), EventState::keyPressed);
	//	input.BindCommand(ControllerButton::Up, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, -1.f }), EventState::keyPressed);
	//	input.BindCommand(ControllerButton::Down, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, 1.f }), EventState::keyPressed);
	//	
	//	input.BindCommand(SDLK_a, std::make_unique<Move>(player.get(), glm::vec2{ -1.f, 0.f }), EventState::keyPressed);
	//	input.BindCommand(SDLK_d, std::make_unique<Move>(player.get(), glm::vec2{ 1.f, 0.f }), EventState::keyPressed);
	//	input.BindCommand(SDLK_w, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, -1.f }), EventState::keyPressed);
	//	input.BindCommand(SDLK_s, std::make_unique<Move>(player.get(), glm::vec2{ 0.f, 1.f }), EventState::keyPressed);
}

int main(int, char* []) {
	Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
