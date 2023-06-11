#include "BombComponent.h"

#include <iostream>
#include <TextureComponent.h>

#include "CollisionManager.h"

dae::BombComponent::BombComponent(GameObject* parent, int tileSize, float fusetime, int range) :
	Component(parent),
	m_TileSize(tileSize),
	m_FuseTime(fusetime),
	m_Range(range)
{
}

void dae::BombComponent::Update(float deltaTime)
{
	m_FuseTime -= deltaTime;
	if (m_FuseTime < 0)
	{
		Explode();
		GetParent()->Destroy();
	}
}

void dae::BombComponent::Render() const
{
}

void dae::BombComponent::Explode()
{
	if (!m_HasExploded)
	{
		GetParent()->RemoveComponent<TextureComponent>();
		auto& collisions = dae::CollisionManager::GetInstance();

		int offset = m_Range * m_TileSize;
		int lenght = (m_Range * 2 + 1) * m_TileSize;
		auto& pos = GetParent()->GetWorldPosition();
		SDL_Rect xRect{ static_cast<int>(pos.x) - offset, static_cast<int>(pos.y), lenght, m_TileSize };
		SDL_Rect yRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) - offset, m_TileSize, lenght };

		auto bricks = collisions.AllBricksInRect(xRect);
		for (auto go : bricks)
		{
			collisions.RemoveWall(go);
			collisions.RemoveBrick(go);
			go.get()->Destroy();
		}
		bricks = collisions.AllBricksInRect(yRect);
		for (auto go : bricks)
		{
			collisions.RemoveWall(go);
			collisions.RemoveBrick(go);
			go.get()->Destroy();
		}

		//	auto bombs = collisions.AllBombsInRect(xRect, m_TileSize);
		//	for (auto go : bombs)
		//	{
		//		go.get()->GetComponent<BombComponent>()->Explode();
		//	}
		//	bombs = collisions.AllBombsInRect(yRect, m_TileSize);
		//	for (auto go : bombs)
		//	{
		//		go.get()->GetComponent<BombComponent>()->Explode();
		//	}

		m_HasExploded = true;
	}
}
