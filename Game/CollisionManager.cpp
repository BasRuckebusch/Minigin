#include "CollisionManager.h"

#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "IngredientComponent.h"

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

void dae::CollisionManager::CollideWithIngredients(const SDL_Rect& col) const
{
	for (auto& gameObject : m_pIngredients)
	{
		int i{0};
		for (const auto colliderComponent : gameObject->GetComponents<BoxColliderComponent>())
		{
			if (colliderComponent->RectInCollider(col))
			{
				gameObject->GetComponent<IngredientComponent>()->HitPart(i);
			}
			i++;
		}
	}
}

void dae::CollisionManager::ChainFall(GameObject* parent, const SDL_Rect& col) const
{
	const float  range{ 1.0f };
	const float  yMin = col.y - range;
	const float  yMax = col.y + range;

	for (auto& gameObject : m_pIngredients)
	{
		if (!(gameObject->GetComponent<IngredientComponent>()->GetFalling()))
		{
			const auto target = gameObject->GetComponent<BoxColliderComponent>();
			if (target->GetRect().x == col.x &&
				target->GetRect().y >= yMin && target->GetRect().y <= yMax)
			{
				gameObject->GetComponent<IngredientComponent>()->Fall();
				parent->GetComponent<IngredientComponent>()->StopFalling();
				//parent->SetLocalPosition(gameObject->GetLocalPosition());
			}
		}
	}
	for (auto& gameObject : m_pStoppers)
	{

		const auto target = gameObject->GetComponent<BoxColliderComponent>();
		if (target->GetRect().x == col.x &&
			target->GetRect().y >= yMin && target->GetRect().y <= yMax)
		{
			parent->GetComponent<IngredientComponent>()->StopFalling();
			int ypos = static_cast<int>(gameObject->GetLocalPosition().y) + 8;
			parent->SetLocalPosition({gameObject->GetLocalPosition().x, ypos, gameObject->GetLocalPosition().z});
			const std::vector<BoxColliderComponent*> colliders = parent->GetComponents<BoxColliderComponent>();
			if (!colliders.empty())
			{
				for (const auto collider : parent->GetComponents<BoxColliderComponent>())
				{
					collider->SetPosition({ gameObject->GetLocalPosition().x, ypos });
				}
			}
		}
	}
}

void dae::CollisionManager::AddLadder(std::shared_ptr<GameObject> object)
{
	m_pLadders.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveLadder(std::shared_ptr<GameObject> object)
{
	std::erase(m_pLadders, object);
}

void dae::CollisionManager::AddIngredient(std::shared_ptr<GameObject> object)
{
	m_pIngredients.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveIngredient(std::shared_ptr<GameObject> object)
{
	std::erase(m_pIngredients, object);
}

void dae::CollisionManager::AddStopper(std::shared_ptr<GameObject> object)
{
	m_pStoppers.emplace_back(std::move(object));
}

void dae::CollisionManager::RemoveStopper(std::shared_ptr<GameObject> object)
{
	std::erase(m_pStoppers, object);
}

void dae::CollisionManager::RemoveAll()
{
	m_pLadders.clear();
	m_pIngredients.clear();
	m_pStoppers.clear();
}
