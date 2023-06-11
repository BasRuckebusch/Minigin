#pragma once
#include "MoveComponent.h"
#include "Renderer.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"


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

	if (GetParent()->HasComponent<CollisionComponent>())
	{
		GetParent()->GetComponent<CollisionComponent>()->SetPosition({ m_XPos, m_YPos });
	}

}

void dae::MoveComponent::Render() const
{
}

void dae::MoveComponent::MoveLeftRight(bool MoveRight)
{
	if (GetParent()->HasComponent<CollisionComponent>())
	{
		auto col = GetParent()->GetComponent<CollisionComponent>();
		auto& collisions = dae::CollisionManager::GetInstance();

		if (MoveRight)
		{
			float newx = m_XPos + m_Speed * m_DeltaTime;
			glm::vec2 newpos{ newx, m_YPos };

			auto rect = col->GetRect();
			rect.x = static_cast<int>(newx);

			if (!collisions.CheckRectCollide(rect))
			{
				m_XPos = newx;
			}
		}
		else
		{
			float newx = m_XPos - m_Speed * m_DeltaTime;
			glm::vec2 newpos{ newx, m_YPos };

			auto rect = col->GetRect();
			rect.x = static_cast<int>(newx);

			if (!collisions.CheckRectCollide(rect))
			{
				m_XPos = newx;
			}
		}
	}
	else
	{
		if (MoveRight)
		{
			m_XPos += m_Speed * m_DeltaTime;
		}
		else
		{
			m_XPos -= m_Speed * m_DeltaTime;
		}
	}
}

void dae::MoveComponent::MoveUpDown(bool MoveDown)
{
	if (GetParent()->HasComponent<CollisionComponent>())
	{
		auto col = GetParent()->GetComponent<CollisionComponent>();
		auto& collisions = dae::CollisionManager::GetInstance();

		if (MoveDown)
		{
			float newy = m_YPos + m_Speed * m_DeltaTime;
			//glm::vec2 newpos{ m_XPos, newy };

			auto rect = col->GetRect();
			rect.y = static_cast<int>(newy);

			if (!collisions.CheckRectCollide(rect))
			{
				m_YPos = newy;
			}
		}
		else
		{
			float newy = m_YPos - m_Speed * m_DeltaTime;
			glm::vec2 newpos{ m_XPos, newy };

			auto rect = col->GetRect();
			rect.y = static_cast<int>(newy);

			if (!collisions.CheckRectCollide(rect))
			{
				m_YPos = newy;
			}
		}
	}
	else
	{
		if (MoveDown)
		{
			m_YPos += m_Speed * m_DeltaTime;
		}
		else
		{
			m_YPos -= m_Speed * m_DeltaTime;
		}
	}
	
}
