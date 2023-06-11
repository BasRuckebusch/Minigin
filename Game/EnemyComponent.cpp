#include "EnemyComponent.h"
#include "BomberManComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"


dae::EnemyComponent::EnemyComponent(GameObject* parent) :
	Component(parent)
{
	auto& pos = GetParent()->GetLocalPosition();
	m_XPos = pos.x;
	m_YPos = pos.y;
	PickNewDirection();
}

void dae::EnemyComponent::Update(float deltaTime)
{
	if (!m_HasKilled)
	{
		m_DeltaTime = deltaTime;

		auto col = GetParent()->GetComponent<CollisionComponent>();
		auto& collisions = dae::CollisionManager::GetInstance();

		auto rect = col->GetRect();
		float speedtime = m_Speed * m_DeltaTime;

		float newx = m_XPos + (m_Direction.x * speedtime);
		rect.x = static_cast<int>(rect.x + (m_Direction.x * speedtime));

		float newy = m_YPos + (m_Direction.y * speedtime);
		rect.y = static_cast<int>(rect.y + (m_Direction.y * speedtime));

		if (!collisions.CheckRectCollide(rect))
		{
			m_XPos = newx;
			m_YPos = newy;

			GameObject* player{nullptr};

			auto players = collisions.AllPlayersInRect(rect);
			for (auto gameObject : players)
			{
				collisions.RemovePlayer(gameObject);
				player = gameObject.get();
			}

			if (player)
			{
				player->GetComponent<BomberManComponent>()->Die();
				m_HasKilled = true;
			}
		}
		else
		{
			PickNewDirection();
		}


		GetParent()->SetLocalPosition({ m_XPos, m_YPos , 0 });

		if (GetParent()->HasComponent<CollisionComponent>())
		{
			GetParent()->GetComponent<CollisionComponent>()->SetPosition({ m_XPos, m_YPos });
		}
	}
}

void dae::EnemyComponent::Render() const
{
}

void dae::EnemyComponent::PickNewDirection()
{
	if (rand() % 2 == 0)
	{
		m_Direction.x = rand() % 2 == 0 ? -1 : 1;
		m_Direction.y = 0;
	}
	else
	{
		m_Direction.x = 0;
		m_Direction.y = rand() % 2 == 0 ? -1 : 1;
	}
}

