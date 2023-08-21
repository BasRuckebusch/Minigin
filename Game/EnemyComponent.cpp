#include "EnemyComponent.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "CollisionManager.h"


dae::EnemyComponent::EnemyComponent(GameObject* parent) :
	Component(parent)
{
	auto& pos = GetParent()->GetLocalPosition();
	m_XPos = pos.x;
	m_YPos = pos.y;
	//PickNewDirection();

	m_GroundLeftCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 4);
	m_GroundLeftCollider->SetOffset({ -2,1 });
	m_GroundRightCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 4);
	m_GroundRightCollider->SetOffset({ 16,1 });
}

void dae::EnemyComponent::Update(float deltaTime)
{
	if (!m_HasKilled)
	{
		m_DeltaTime = deltaTime;
	
		//auto col = GetParent()->GetComponent<BoxColliderComponent>();
		//auto& collisions = CollisionManager::GetInstance();
	
		//auto rect = col->GetRect();
		float speedtime = m_Speed * m_DeltaTime;
	
		float newx = m_XPos + (m_Direction.x * speedtime);
		//rect.x = static_cast<int>(rect.x + (m_Direction.x * speedtime));
	
		float newy = m_YPos + (m_Direction.y * speedtime);
		//rect.y = static_cast<int>(rect.y + (m_Direction.y * speedtime));
	
		m_XPos = newx;
		m_YPos = newy;

		GetParent()->SetLocalPosition({ m_XPos, m_YPos , 0 });

		if (const std::vector<BoxColliderComponent*> colliders = GetParent()->GetComponents<BoxColliderComponent>(); !colliders.empty())
			for (const auto collider : GetParent()->GetComponents<BoxColliderComponent>())
				collider->SetPosition({ m_XPos, m_YPos });


		if (CanMoveLeft() && !CanMoveRight())
		{
			m_Direction.x = -1;
		}
		if (!CanMoveLeft() && CanMoveRight())
		{
			m_Direction.x = 1;
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

bool dae::EnemyComponent::CanMoveLeft() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_GroundLeftCollider->GetRect()))
		return true;
	return false;
}

bool dae::EnemyComponent::CanMoveRight() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_GroundRightCollider->GetRect()))
		return true;
	return false;
}

