#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

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
	player->AddComponent<TextureComponent>("player.tga");
	//player->AddComponent<TextComponent>("PLAYER", fpsfont, SDL_Color(255, 0, 0));
	player->AddComponent<MoveComponent>();
	player->SetLocalPosition(glm::vec3(256, 280, 0));
	scene.Add(player);

	InputManager::GetInstance().AddPlayer(player.get());

	const auto player2 = std::make_shared<GameObject>();
	player2->AddComponent<TextureComponent>("enemy.tga");
	player2->AddComponent<MoveComponent>();
	player2->SetLocalPosition(glm::vec3(256, 300, 0));
	scene.Add(player2);

	InputManager::GetInstance().AddPlayer(player2.get());

	scene.Remove(go);

	const std::string title = ResourceManager::GetInstance().LoadSound("TitleScreen.mp3");
	const auto titleID = ServiceLocator::GetSoundSystem().AddSound(title.c_str());

	ServiceLocator::GetSoundSystem().Play(titleID, 50.f);

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