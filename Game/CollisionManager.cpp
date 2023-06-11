#include "CollisionManager.h"

#include "CollisionComponent.h"
#include "GameObject.h"

bool dae::CollisionManager::CheckPointInWall(const glm::vec2& point)
{
	for (auto& pWall : m_pWalls)
	{
		if (pWall.get()->HasComponent<CollisionComponent>())
		{
			auto col = pWall.get()->GetComponent<CollisionComponent>();
			if (col->PointInCollider(point))
			{
				return true;
			}
		}
	}
	return false;
}

bool dae::CollisionManager::CheckRectCollide(const SDL_Rect& col)
{
	for (auto& pWall : m_pWalls)
	{
		if (pWall.get()->HasComponent<CollisionComponent>())
		{
			auto collider = pWall.get()->GetComponent<CollisionComponent>();
			if (collider->DoesCollide(col))
			{
				return true;
			}
		}
	}
	return false;
}

void dae::CollisionManager::AddWall(std::shared_ptr<GameObject> object)
{
	m_pWalls.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveWall(std::shared_ptr<GameObject> object)
{
	std::erase(m_pWalls, object);
}

void dae::CollisionManager::AddPlayer(std::shared_ptr<GameObject> object)
{
	m_pPlayers.emplace_back(std::move(object));
}

void dae::CollisionManager::RemovePlayer(std::shared_ptr<GameObject> object)
{
	std::erase(m_pPlayers, object);
}

void dae::CollisionManager::RemoveAll()
{
	m_pWalls.clear();
	m_pPlayers.clear();
}
