#include "Command.h"
#include "GameObject.h"
#include "MoveComponent.h"


void dae::Command::Execute()
{
}

void dae::Command::Execute([[maybe_unused]] GameObject& actor)
{
}

void dae::MoveCommand::Execute(GameObject& actor)
{
	actor.GetComponent<MoveComponent>()->SetDirection(m_Direction);
}
