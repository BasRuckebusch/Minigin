#include <SDL.h>
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//#include <vld.h>
#endif
#include "Minigin.h"

#include "FPSComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "Utils.h"

using namespace dae;

void load()
{
	std::unique_ptr<SoundSystem> ss = std::make_unique<SDLSoundSystem>();
	ServiceLocator::RegisterSoundSystem(std::move(ss));

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	const auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	// Camera and background
	auto& renderer = Renderer::GetInstance();
	renderer.SetBackgroundColor(SDL_Color(57, 132, 0));
	renderer.SetCameraPosition(glm::vec2(0, -32));
	renderer.SetCameraScale(2.f);

	// Load scene from file
	int tileSize{ 16 };

	std::string file{ ResourceManager::GetInstance().GetFullFilePath("bombtest.bmp") };
	glm::vec2 worldPos = { 0, 0 };
	LoadLevelFromBMP(file, &scene, worldPos, tileSize);

	// FPS counter
	auto go = std::make_shared<GameObject>();
	const auto fpsfont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>();
	go->AddComponent<TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	go->AddComponent<FPSComponent>();
	go->SetPosition(0, -16);
	scene.Add(go);

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
