#pragma once
#include "MoveComponent.h"
#include "Renderer.h"
#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "PeterComponent.h"


dae::MoveComponent::MoveComponent(GameObject* parent) :
	Component(parent)
{
	auto& pos = GetParent()->GetLocalPosition();
	m_XPos = pos.x;
	m_YPos = pos.y;
}

void dae::MoveComponent::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	GetParent()->SetLocalPosition({ m_XPos, m_YPos , 0});

	const std::vector<BoxColliderComponent*> colliders = GetParent()->GetComponents<BoxColliderComponent>();
	if (!colliders.empty())
	{
		for (const auto collider : GetParent()->GetComponents<BoxColliderComponent>())
		{
			collider->SetPosition({ m_XPos, m_YPos });
		}
	}
}

void dae::MoveComponent::Render() const
{
}

void dae::MoveComponent::Move(glm::vec2 direction)
{
	if (GetParent()->HasComponent<PeterComponent>())
	{
		const auto& peter = GetParent()->GetComponent<PeterComponent>();

		if (peter->CanMoveLeft() && direction.x < 0)
			m_XPos += direction.x * m_Speed * m_DeltaTime;
		else if (peter->CanMoveRight() && direction.x > 0)
			m_XPos += direction.x * m_Speed * m_DeltaTime;
		if (direction.y > 0 && peter->CanMoveDown())
			m_YPos += direction.y * m_Speed * m_DeltaTime;
		else if(direction.y < 0 && peter->CanMoveUp())
			m_YPos += direction.y * m_Speed * m_DeltaTime;
	}
	else
	{
		m_XPos += direction.x * m_Speed * m_DeltaTime;
		m_YPos += direction.y * m_Speed * m_DeltaTime;
	}
}
