#include "PeterComponent.h"

#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "utils.h"

dae::PeterComponent::PeterComponent(GameObject* parent, bool isEvil, Scene* scene, std::string levelName):
	Component(parent),
	m_IsEvil(isEvil),
	m_pScene(scene),
	m_LevelName(std::move(levelName))
{
	m_LeftCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 5, 5);
	m_LeftCollider->SetOffset({ -1,14 });
	m_RightCollider = GetParent()->AddComponent<BoxColliderComponent>(GetParent()->GetWorldPosition(), 5, 5);
	m_RightCollider->SetOffset({ 11,14 });

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
	if (!m_IsEvil)
	{
		const auto& collisions = CollisionManager::GetInstance();
		collisions.CollideWithIngredients(m_LeftCollider->GetRect());
		collisions.CollideWithIngredients(m_RightCollider->GetRect());

		if (collisions.IsCollidingWithEnemy(m_GroundLeftCollider->GetRect()) || collisions.IsCollidingWithEnemy(m_GroundRightCollider->GetRect()))
		{
			Die();
		}
	}
	
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

void dae::PeterComponent::Die()
{
	if (!m_Dead)
	{
		if (m_pScene != nullptr)
		{
			LoadMenu(m_LevelName, m_pScene);
			m_Dead = true;
		}
	}
}
