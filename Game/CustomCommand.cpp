#include "CustomCommand.h"

#include "BomberManComponent.h"
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
	m_pGameObject->GetComponent<BomberManComponent>()->PlaceBomb(m_pScene);
}
