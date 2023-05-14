#include "MoveComponent.h"

dae::MoveComponent::MoveComponent(GameObject* parent) :
	Component(parent)
{
}

void dae::MoveComponent::Update(float deltaTime)
{
	auto pos = GetParent()->GetLocalPosition();
	pos.x += m_Direction.x * m_Speed * deltaTime;
	pos.y += m_Direction.y * m_Speed * deltaTime;;
	GetParent()->SetLocalPosition(pos);
}

void dae::MoveComponent::Render() const
{
}