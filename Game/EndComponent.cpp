#include "EndComponent.h"

#include <iostream>

#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "CustomCommand.h"


dae::EndComponent::EndComponent(GameObject* parent, Scene* pScene, std::vector<std::string> levelNames) :
	Component(parent),
	m_pScene(pScene),
	m_LevelNames(std::move(levelNames))
{
}

void dae::EndComponent::Update(float)
{
	const auto& collisions = CollisionManager::GetInstance();
	if (!m_Ended)
	{
		if (collisions.GetAmountPots() <= 0)
			m_Ended = true;
	}
	else
	{
		if (collisions.GetAmountPots() > 0)
		{
			m_Ended = false;
		}
		else
		{
			auto load = NextLevel(m_pScene, m_LevelNames);
			load.Execute();
		}
	}
}

void dae::EndComponent::Render() const
{
}
