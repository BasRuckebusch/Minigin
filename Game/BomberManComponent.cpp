#include "BomberManComponent.h"
#include "BombComponent.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include <Utils.h>
#include "CustomCommand.h"


dae::BomberManComponent::BomberManComponent(GameObject* parent, Scene* scene, int tileSize) :
	Component(parent),
	m_pScene(scene),
	m_TileSize(tileSize)
{
}

void dae::BomberManComponent::Update(float deltaTime)
{
	m_BombElapsed -= deltaTime;

}

void dae::BomberManComponent::Render() const
{
}

void dae::BomberManComponent::PlaceBomb()
{
	if (m_BombElapsed <= 0 && m_Bombs < m_MaxBombs)
	{
		glm::vec2 tilePos = GetParent()->GetWorldPosition();
		tilePos.x = std::round(tilePos.x / m_TileSize) * m_TileSize;
		tilePos.y = std::round(tilePos.y / m_TileSize) * m_TileSize;

		auto go = std::make_shared<dae::GameObject>();
		go->AddComponent<dae::TextureComponent>("bomb.tga");
		go->SetPosition(tilePos.x, tilePos.y);
		go->AddComponent<dae::BombComponent>(m_TileSize, m_Fuse, m_Range);
		m_pScene->Add(go);

		m_BombElapsed = m_BombTimer;
		m_Bombs++;
	}
}

void dae::BomberManComponent::GiveBomb()
{
	m_Bombs--;
}

void dae::BomberManComponent::Die()
{
	if (!m_Dead)
	{
		if (m_pScene != nullptr)
		{
			//LoadLevel(m_LevelName, m_pScene);
			auto load = LevelLoad(m_pScene, m_LevelName);
			load.Execute();
			m_Dead = true;
		}
		
	}
	
}
