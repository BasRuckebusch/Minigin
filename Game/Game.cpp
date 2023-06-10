#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
//#include <vld.h>
#endif
#include <iostream>

#include "Minigin.h"


#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureComponent.h"

using namespace dae;

void load()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<GameObject>();
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
