#include "BomberManComponent.h"
#include <iostream>

#include "BombComponent.h"
#include "Scene.h"
#include "TextureComponent.h"

dae::BomberManComponent::BomberManComponent(GameObject* parent, int tileSize) :
	Component(parent),
	m_TileSize(tileSize)
{
}

void dae::BomberManComponent::Update(float)
{
}

void dae::BomberManComponent::Render() const
{
}

void dae::BomberManComponent::PlaceBomb(Scene* scene)
{
	glm::vec2 tilePos = GetParent()->GetWorldPosition();
	tilePos.x = std::round(tilePos.x / m_TileSize) * m_TileSize;
	tilePos.y = std::round(tilePos.y / m_TileSize) * m_TileSize;

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("bomb.tga");
	go->SetPosition(tilePos.x, tilePos.y);
	go->AddComponent<dae::BombComponent>(16, 1.f, 1);
	scene->Add(go);
	//std::cout << tilePos.x << " - " << tilePos.y << "\n";
}
