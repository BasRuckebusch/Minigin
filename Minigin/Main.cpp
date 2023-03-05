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
#include "RotateComponent.h"

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto go = std::make_shared<dae::GameObject>();
	auto texture = new TextureComponent("background.tga");
	go->AddComponent(texture);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	texture = new TextureComponent("logo.tga");
	go->AddComponent(texture);
	go->SetPosition(216, 180);
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	texture = new TextureComponent();
	const auto text = new TextComponent("Programming 4 Assignment", font);
	go->AddComponent(texture);
	go->AddComponent(text);
	go->SetPosition(80, 20);
	scene.Add(go);
	
	go = std::make_shared<dae::GameObject>();
	texture = new TextureComponent();
	const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	const auto text2 = new TextComponent("0", fpsfont, SDL_Color(0,255,0));
	const auto fps = new FPSComponent();
	go->AddComponent(texture);
	go->AddComponent(text2);
	go->AddComponent(fps);
	go->SetPosition(0, 5);;
	scene.Add(go);

	const auto parent = std::make_shared<dae::GameObject>();
	texture = new TextureComponent("player.tga");
	auto rotate = new RotateComponent(0.3f);
	parent->AddComponent(texture);
	parent->AddComponent(rotate);
	parent->SetLocalPosition(glm::vec3(256, 280, 0));
	scene.Add(parent);

	const auto child = std::make_shared<dae::GameObject>();
	texture = new TextureComponent("enemy.tga");
	rotate = new RotateComponent(0.3f);
	child->AddComponent(texture);
	child->AddComponent(rotate);
	child->SetLocalPosition(glm::vec3(256, 280, 0));
	child->SetParent(parent, true);
	scene.Add(child);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}