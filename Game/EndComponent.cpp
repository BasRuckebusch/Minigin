#include "EndComponent.h"
#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "CustomCommand.h"


dae::EndComponent::EndComponent(GameObject* parent, Scene* pScene, std::vector<std::string> levelNames) :
	Component(parent),
	m_pScene(pScene),
	m_LevelNames(levelNames)
{
	auto col = GetParent()->GetComponent<BoxColliderComponent>();
	m_Rect = col->GetRect();
}

void dae::EndComponent::Update(float)
{
	//if (!m_Ended)
	//{
	//	auto& collisions = dae::CollisionManager::GetInstance();
	//
	//	if (collisions.GetAmountEnemies() <= 0)
	//	{
	//		if (!collisions.AllPlayersInRect(m_Rect).empty())
	//		{
	//			m_Ended = true;
	//		}
	//	}
	//	
	//}
	//else
	//{
	//	auto load = NextLevel(m_pScene, m_LevelNames);
	//	load.Execute();
	//}

}

void dae::EndComponent::Render() const
{
}
