#include "EnemyComponent.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "PeterComponent.h"


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
	
		//auto col = GetParent()->GetComponent<BoxColliderComponent>();
		//auto& collisions = CollisionManager::GetInstance();

		PickNewDirection();

		GetParent()->SetLocalPosition({ m_XPos, m_YPos , 0 });
	
		if (GetParent()->HasComponent<BoxColliderComponent>())
		{
			GetParent()->GetComponent<BoxColliderComponent>()->SetPosition({ m_XPos, m_YPos });
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

