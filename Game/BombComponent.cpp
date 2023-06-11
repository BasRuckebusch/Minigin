#pragma once
#include "BombComponent.h"
#include <TextureComponent.h>
#include "CollisionManager.h"
#include "BomberManComponent.h"

dae::BombComponent::BombComponent(dae::GameObject* parent,  int tileSize, float fusetime, int range) :
	Component(parent),
	m_TileSize(tileSize),
	m_Range(range),
	m_FuseTime(fusetime)
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

		auto players = collisions.AllPlayersInRect(xRect);
		for (auto go : players)
		{
			collisions.RemovePlayer(go);
			go.get()->GetComponent<BomberManComponent>()->Die();
		}
		players = collisions.AllPlayersInRect(yRect);
		for (auto go : players)
		{
			collisions.RemovePlayer(go);
			go.get()->GetComponent<BomberManComponent>()->Die();
		}

		auto enemies = collisions.AllEnemiesInRect(xRect);
		for (auto go : enemies)
		{
			collisions.RemoveEnemy(go);
			go.get()->Destroy();
		}
		enemies = collisions.AllPlayersInRect(yRect);
		for (auto go : enemies)
		{
			collisions.RemoveEnemy(go);
			go.get()->Destroy();
		}

		players = collisions.GetPlayers();
		for (auto go : players)
		{
			go.get()->GetComponent<BomberManComponent>()->GiveBomb();
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
