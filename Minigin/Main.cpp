#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include "Command.h"
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "MoveComponent.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"

using namespace dae;

void load()
{
	std::unique_ptr<SoundSystem> ss = std::make_unique<SDLSoundSystem>();
	ServiceLocator::RegisterSoundSystem(std::move(ss));

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->SetPosition(80, 20);
	scene.Add(go);

	const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->AddComponent<TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	go->AddComponent<FPSComponent>();
	go->SetPosition(0, 5);
	scene.Add(go);

	const auto player = std::make_shared<GameObject>();
	player->SetLocalPosition(glm::vec3(256, 280, 0));
	player->AddComponent<TextureComponent>("player.tga");
	//player->AddComponent<TextComponent>("PLAYER", fpsfont, SDL_Color(255, 0, 0));
	player->AddComponent<MoveComponent>();
	scene.Add(player);

	InputManager::GetInstance().AddPlayer(player.get());

	const auto player2 = std::make_shared<GameObject>();
	player2->SetLocalPosition(glm::vec3(256, 300, 0));
	player2->AddComponent<TextureComponent>("enemy.tga");
	player2->AddComponent<MoveComponent>();
	scene.Add(player2);

	InputManager::GetInstance().AddPlayer(player2.get());

	scene.Remove(go);

	const std::string title = ResourceManager::GetInstance().LoadSound("TitleScreen.mp3");
	const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());

	ServiceLocator::GetSoundSystem().Play(titleID, 50.f);

	//INPUT

	//InputManager::GetInstance().BindCommand(XINPUT_GAMEPAD_DPAD_LEFT, new MoveLeftRight(player.get(), false));
	//InputManager::GetInstance().BindCommand(XINPUT_GAMEPAD_DPAD_RIGHT, new MoveLeftRight(player.get(), true));
	//InputManager::GetInstance().BindCommand(XINPUT_GAMEPAD_DPAD_UP, new MoveUpDown(player.get(), false));
	//InputManager::GetInstance().BindCommand(XINPUT_GAMEPAD_DPAD_DOWN, new MoveUpDown(player.get(), true));

	InputManager::GetInstance().BindCommand(SDL_SCANCODE_LEFT, new MoveLeftRight(player.get(), false));
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_RIGHT, new MoveLeftRight(player.get(), true));
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_UP, new MoveUpDown(player.get(), false));
	InputManager::GetInstance().BindCommand(SDL_SCANCODE_DOWN, new MoveUpDown(player.get(), true));
	
	InputManager::GetInstance().BindCommand(SDLK_a, new MoveLeftRight(player2.get(), false));
	InputManager::GetInstance().BindCommand(SDLK_d, new MoveLeftRight(player2.get(), true));
	InputManager::GetInstance().BindCommand(SDLK_w, new MoveUpDown(player2.get(), false));
	InputManager::GetInstance().BindCommand(SDLK_s, new MoveUpDown(player2.get(), true));

	//	const auto parent = std::make_shared<dae::GameObject>();
	//	texture = new TextureComponent("enemy.tga");
	//	auto rotate = new RotateComponent(0.1f);
	//	parent->AddComponent(texture);
	//	parent->AddComponent(rotate);
	//	parent->SetLocalPosition(glm::vec3(256, 280, 0));
	//	scene.Add(parent);
	//	
	//	const auto child = std::make_shared<dae::GameObject>();
	//	texture = new TextureComponent("enemy.tga");
	//	//rotate = new RotateComponent(0.1f);
	//	child->AddComponent(texture);
	//	//child->AddComponent(rotate);
	//	child->SetLocalPosition(glm::vec3(256, 300, 0));
	//	child->SetParent(parent, true);
	//	scene.Add(child);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}