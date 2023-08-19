#include "CollisionManager.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"

//	bool dae::CollisionManager::CheckPointInWall(const glm::vec2& point)
//	{
//		for (auto& pWall : m_pWalls)
//		{
//			if (pWall.get()->HasComponent<BoxColliderComponent>())
//			{
//				auto col = pWall.get()->GetComponent<BoxColliderComponent>();
//				if (col->PointInCollider(point))
//				{
//					return true;
//				}
//			}
//		}
//		return false;
//	}

//bool dae::CollisionManager::CheckRectCollide(const SDL_Rect& col)
//{
//	for (auto& pWall : m_pWalls)
//	{
//		if (pWall.get()->HasComponent<BoxColliderComponent>())
//		{
//			auto collider = pWall.get()->GetComponent<BoxColliderComponent>();
//			if (collider->RectInCollider(col))
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}


bool dae::CollisionManager::IsCollidingWithLadder(const SDL_Rect& col) const
{
	for (auto& gameObject : m_pLadders)
	{
		for (const auto colliderComponent : gameObject->GetComponents<BoxColliderComponent>())
		{
			if (colliderComponent->RectInCollider(col))
			{
				return true;
			}
		}
	}
	return false;
}

void dae::CollisionManager::AddLadder(std::shared_ptr<GameObject> object)
{
	m_pLadders.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveLadder(std::shared_ptr<GameObject> object)
{
	std::erase(m_pLadders, object);
}

void dae::CollisionManager::RemoveAll()
{
	m_pLadders.clear();
}
