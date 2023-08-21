#include "CustomCommand.h"

#include "Utils.h"
#include "GameObject.h"
#include "MenuComponent.h"
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
	LoadLevel(m_LevelNames[m_Id], m_pScene, 0);
}

void dae::MenuLoad::Execute()
{
	LoadMenu(m_LevelName, m_pScene);
}

void dae::LevelLoad::Execute()
{
	//LoadLevel(m_LevelName, m_pScene);
}

void dae::MenuMove::Execute()
{
	if (!m_pGameObject->IsDestroyed())
		if (m_pGameObject->HasComponent<MenuComponent>())
			m_pGameObject->GetComponent<MenuComponent>()->Move(m_Up);
	
}

void dae::MenuSelect::Execute()
{
	if (!m_pGameObject->IsDestroyed())
		if (m_pGameObject->HasComponent<MenuComponent>())
			m_pGameObject->GetComponent<MenuComponent>()->Select();
}
