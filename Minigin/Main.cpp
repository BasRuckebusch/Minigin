#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
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

using namespace dae;

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto text = new TextComponent("Programming 4 Assignment", font);
	go->AddComponent(text);
	go->SetPosition(80, 20);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	const auto text2 = new TextComponent("0", font);
	auto fps = new FPSComponent();
	go->AddComponent(text2);
	go->AddComponent(fps);
	go->SetPosition(216, 260);;
	scene.Add(go);

	

	//	auto go = std::make_shared<dae::GameObject>();
	//	go->SetTexture("background.tga");
	//	scene.Add(go);
	//	
	//	go = std::make_shared<dae::GameObject>();
	//	go->SetTexture("logo.tga");
	//	go->SetPosition(216, 180);
	//	scene.Add(go);
	//	
	//	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	//	to->SetPosition(80, 20);
	//	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}