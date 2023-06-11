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
			const auto collider = pBrick.get()->GetComponent<CollisionComponent>();
			if (collider->DoesCollide(rect))
			{
				result.push_back(pBrick);
			}
		}
	}

	return result;
}

std::vector<std::shared_ptr<dae::GameObject>> dae::CollisionManager::AllPlayersInRect(const SDL_Rect& rect)
{
	std::vector<std::shared_ptr<GameObject>> result{};

	for (auto& pPlayer : m_pPlayers)
	{
		if (pPlayer.get()->HasComponent<CollisionComponent>())
		{
			const auto collider = pPlayer.get()->GetComponent<CollisionComponent>();
			if (collider->DoesCollide(rect))
			{
				result.push_back(pPlayer);
			}
		}
	}

	return result;
}

std::vector<std::shared_ptr<dae::GameObject>> dae::CollisionManager::AllEnemiesInRect(const SDL_Rect& rect)
{
	std::vector<std::shared_ptr<GameObject>> result{};

	for (auto& pEnemy : m_pEnemies)
	{
		if (pEnemy.get()->HasComponent<CollisionComponent>())
		{
			const auto collider = pEnemy.get()->GetComponent<CollisionComponent>();
			if (collider->DoesCollide(rect))
			{
				result.push_back(pEnemy);
			}
		}
	}

	return result;
}

//	std::vector<std::shared_ptr<dae::GameObject>> dae::CollisionManager::AllBombsInRect(const SDL_Rect& rect, int tileSize)
//	{
//		std::vector<std::shared_ptr<GameObject>> result{};
//	
//		for (auto& pBomb : m_pBombs)
//		{
//			//	const auto pos = pBomb.get()->GetWorldPosition();
//			//	SDL_Rect bRect{ static_cast<int>(pos.x), static_cast<int>(pos.y), tileSize, tileSize };
//			//	if (SDL_HasIntersection(&bRect, &rect))
//			//	{
//			//		result.push_back(pBomb);
//			//	}
//		}
//	
//		return result;
//	}

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

void dae::CollisionManager::AddBomb(std::shared_ptr<GameObject> object)
{
	m_pBombs.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveBomb(std::shared_ptr<GameObject> object)
{
	std::erase(m_pBombs, object);
}

void dae::CollisionManager::AddPlayer(std::shared_ptr<GameObject> object)
{
	m_pPlayers.emplace_back(std::move(object));
}

void dae::CollisionManager::RemovePlayer(std::shared_ptr<GameObject> object)
{
	std::erase(m_pPlayers, object);
}

void dae::CollisionManager::AddEnemy(std::shared_ptr<GameObject> object)
{
	m_pEnemies.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveEnemy(std::shared_ptr<GameObject> object)
{
	std::erase(m_pEnemies, object);
}

void dae::CollisionManager::RemoveAll()
{
	m_pWalls.clear();
	m_pPlayers.clear();
	m_pEnemies.clear();
	m_pBricks.clear();
	m_pBombs.clear();
}
