#include "MoveComponent.h"

#include <iostream>

#include "Renderer.h"

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

	//	auto pos = GetParent()->GetLocalPosition();
	//	pos.x += m_Direction.x * m_Speed * deltaTime;
	//	pos.y += m_Direction.y * m_Speed * deltaTime;;
	//	GetParent()->SetLocalPosition(pos);
}

void dae::MoveComponent::Render() const
{
}

void dae::MoveComponent::MoveLeftRight(bool MoveRight)
{
	//	if (MoveRight)
	//		m_XPos += m_Speed * m_DeltaTime;
	//	else
	//		m_XPos -= m_Speed * m_DeltaTime;
	if (MoveRight)
	{
		m_XPos += m_Speed * m_DeltaTime;
	}
	else
	{
		m_XPos -= m_Speed * m_DeltaTime;
	}
}

void dae::MoveComponent::MoveUpDown(bool MoveDown)
{
	//	if (MoveDown)
	//		m_YPos += m_Speed * m_DeltaTime;
	//	else
	//		m_YPos -= m_Speed * m_DeltaTime;

	if (MoveDown)
	{
		m_YPos += m_Speed * m_DeltaTime;
	}
	else
	{
		m_YPos -= m_Speed * m_DeltaTime;
	}
}
