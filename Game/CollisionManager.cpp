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

std::vector<std::shared_ptr<dae::GameObject>> dae::CollisionManager::AllBricksInRect(const SDL_Rect& rect)
{
	std::vector<std::shared_ptr<GameObject>> result{};

	for (auto& pBrick : m_pBricks)
	{
		if (pBrick.get()->HasComponent<CollisionComponent>())
		{
			auto collider = pBrick.get()->GetComponent<CollisionComponent>();
			if (collider->DoesCollide(rect))
			{
				result.push_back(pBrick);
			}
		}
	}

	return result;
}

void dae::CollisionManager::AddWall(std::shared_ptr<GameObject> object)
{
	m_pWalls.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveWall(std::shared_ptr<GameObject> object)
{
	std::erase(m_pWalls, object);
}

void dae::CollisionManager::AddBrick(std::shared_ptr<GameObject> object)
{
	m_pBricks.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveBrick(std::shared_ptr<GameObject> object)
{
	std::erase(m_pBricks, object);
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
