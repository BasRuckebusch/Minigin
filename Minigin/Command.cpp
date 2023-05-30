#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"


void dae::Command::Execute()
{
}

void dae::MoveCommand::Execute()
{
	m_pGameObject->GetComponent<MoveComponent>()->SetDirection(m_Direction);
}
