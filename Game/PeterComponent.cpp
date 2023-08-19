#include "PeterComponent.h"

#include <iostream>

#include "BoxColliderComponent.h"
#include "CollisionManager.h"

dae::PeterComponent::PeterComponent(dae::GameObject* parent) :
	Component(parent)
{
	m_LeftCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 4, 5);
	m_LeftCollider->SetOffset({ 0,14 });
	m_RightCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 4, 5);
	m_RightCollider->SetOffset({ 10,14 });

	m_DownCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 5);
	m_DownCollider->SetOffset({ 7,15 });
	m_UpCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 10);
	m_UpCollider->SetOffset({ 7,8 });

	m_GroundLeftCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 4);
	m_GroundLeftCollider->SetOffset({ -2,1 });
	m_GroundRightCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 2, 4);
	m_GroundRightCollider->SetOffset({ 16,1});
}

void dae::PeterComponent::Update(float)
{
}

void dae::PeterComponent::Render() const
{
	Component::Render();
}

bool dae::PeterComponent::IsOnLadder() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_LeftCollider->GetRect()) 
		&& collisions.IsCollidingWithLadder(m_RightCollider->GetRect()))
		return true;

	return false;
}

bool dae::PeterComponent::CanMoveDown() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_DownCollider->GetRect()) && IsOnLadder())
		return true;
	return false;
}

bool dae::PeterComponent::CanMoveUp() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if ((collisions.IsCollidingWithLadder(m_UpCollider->GetRect())) && IsOnLadder())
		return true;
	return false;
}

bool dae::PeterComponent::CanMoveLeft() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_GroundLeftCollider->GetRect()))
		return true;
	return false;
}

bool dae::PeterComponent::CanMoveRight() const
{
	const auto& collisions = CollisionManager::GetInstance();
	if (collisions.IsCollidingWithLadder(m_GroundRightCollider->GetRect()))
		return true;
	return false;
}