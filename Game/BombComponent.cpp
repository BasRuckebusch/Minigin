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
		GetParent()->RemoveComponent<TextureComponent>();
		auto& collisions = dae::CollisionManager::GetInstance();

		int lenght = m_Range * m_TileSize;
		auto& pos =  GetParent()->GetWorldPosition();
		SDL_Rect xRect{ static_cast<int>(pos.x) - lenght, static_cast<int>(pos.y), lenght * 3, m_TileSize };
		SDL_Rect yRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) - lenght, m_TileSize, lenght * 3 };

		std::cout << xRect.x << " - " << xRect.y << " - " << xRect.w << " - " << xRect.h << "\n";
		std::cout << yRect.x << " - " << yRect.y << " - " << yRect.w << " - " << yRect.h << "\n";

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

	}
	if (m_FuseTime < -0.2)
	{
		GetParent()->Destroy();
	}
}

void dae::BombComponent::Render() const
{
}