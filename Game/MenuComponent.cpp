#include "MenuComponent.h"
#include "utils.h"

dae::MenuComponent::MenuComponent(GameObject* parent, const std::string& levelName, Scene* scene) :
	Component(parent),
	m_LevelName(levelName),
	m_pScene(scene)
{
}

void dae::MenuComponent::Update(float)
{
}

void dae::MenuComponent::Render() const
{
}

void dae::MenuComponent::Move(const bool up)
{

	auto& pos = GetParent()->GetLocalPosition();
	float xPos = pos.x;
	float yPos = pos.y;

	constexpr int distance{ 49 };
	if (up && m_GameMode != 0)
	{
		m_GameMode--;
		yPos -= distance;
		GetParent()->SetLocalPosition({ xPos, yPos , 0 });
	}
	else if (!up && m_GameMode != 2)
	{
		m_GameMode++;
		yPos += distance;
		GetParent()->SetLocalPosition({ xPos, yPos , 0 });
	}
}

void dae::MenuComponent::Select() const
{
	LoadLevel(m_LevelName, m_pScene, m_GameMode);
}
