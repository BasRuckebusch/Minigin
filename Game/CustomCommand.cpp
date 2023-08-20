#include "CustomCommand.h"

#include "Utils.h"
#include "GameObject.h"
#include "MoveComponent.h"


void dae::Move::Execute()
{
	m_pGameObject->GetComponent<MoveComponent>()->Move(m_Direction);
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

void dae::LevelLoad::Execute()
{
	//LoadLevel(m_LevelName, m_pScene);
}
