#include "CollisionManager.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "IngredientComponent.h"


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

bool dae::CollisionManager::IsCollidingWithEnemy(const SDL_Rect& col) const
{
	for (auto& gameObject : m_pEnemies)
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

void dae::CollisionManager::ChainFall(GameObject* parent, const SDL_Rect& col) const
{
	const float  range{ 1.0f };
	const float  yMin = col.y - range;
	const float  yMax = col.y + range;
	const int  tileSize{ 8 };

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
			int ypos = static_cast<int>(gameObject->GetLocalPosition().y) + tileSize;
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
	for (auto& gameObject : m_pPots)
	{
		const auto target = gameObject->GetComponent<BoxColliderComponent>();
		if (target->GetRect().x == col.x &&
			target->GetRect().y >= yMin && target->GetRect().y <= yMax)
		{
			parent->GetComponent<IngredientComponent>()->StopFalling();
			int ypos = static_cast<int>(gameObject->GetLocalPosition().y) + tileSize;
			parent->SetLocalPosition({ gameObject->GetLocalPosition().x, ypos, gameObject->GetLocalPosition().z });
			const std::vector<BoxColliderComponent*> colliders = parent->GetComponents<BoxColliderComponent>();
			if (!colliders.empty())
			{
				for (const auto collider : parent->GetComponents<BoxColliderComponent>())
				{
					collider->SetPosition({ gameObject->GetLocalPosition().x, ypos });
				}
			}
			auto pos = gameObject->GetLocalPosition();
			pos.y -= tileSize;
			gameObject->SetLocalPosition(pos);
			const std::vector<BoxColliderComponent*> colliders2 = gameObject->GetComponents<BoxColliderComponent>();
			if (!colliders2.empty())
			{
				for (const auto collider : gameObject->GetComponents<BoxColliderComponent>())
				{
					collider->SetPosition({ pos.x, pos.y });
				}
			}
		}
		
	}
}

void dae::CollisionManager::InPot(GameObject* , const SDL_Rect& col)
{
	const int  tileSize{ 8 };
	const float  range{ 1.0f };
	const float  yMin = col.y - range;
	const float  yMax = col.y + tileSize + range;
	

	for (const auto& gameObject : m_pPots)
	{
		const auto target = gameObject->GetComponent<BoxColliderComponent>();
		if (target->GetRect().x == col.x &&
			target->GetRect().y >= yMin && target->GetRect().y <= yMax)
		{
			m_FilledPots++;
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

void dae::CollisionManager::AddPot(std::shared_ptr<GameObject> object)
{
	m_pPots.emplace_back(std::move(object));
	m_FilledPots = 0;
}

void dae::CollisionManager::RemovePot(std::shared_ptr<GameObject> object)
{
	std::erase(m_pPots, object);
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
	m_pLadders.clear();
	m_pIngredients.clear();
	m_pStoppers.clear();
	m_pPots.clear();
	m_pEnemies.clear();
}
