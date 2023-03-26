#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"

void dae::MoveCommand::Execute(GameObject& actor)
{
	actor.GetComponent<MoveComponent>()->SetDirection(m_Direction);
}
