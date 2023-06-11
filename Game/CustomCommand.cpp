#include "CustomCommand.h"
#include "Utils.h"
#include "GameObject.h"
#include "MoveComponent.h"


void dae::MoveCommand::Execute()
{
	m_pGameObject->GetComponent<MoveComponent>()->SetDirection(m_Direction);
}

void dae::MoveLeftRight::Execute()
{
	m_pGameObject->GetComponent<MoveComponent>()->MoveLeftRight(m_MoveRight);
}

void dae::MoveUpDown::Execute()
{
	m_pGameObject->GetComponent<MoveComponent>()->MoveUpDown(m_MoveDown);
}

void dae::PlaceBomb::Execute()
{
	m_pGameObject->GetComponent<BomberManComponent>()->PlaceBomb();
}

void dae::NextLevel::Execute()
{
	m_Id++;
	if (m_Id == static_cast<int>(m_LevelNames.size()))
	{
		m_Id = 0;
	}
	LoadLevel(m_LevelNames[m_Id], m_pScene);
}
