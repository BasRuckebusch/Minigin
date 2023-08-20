#include "ScoreComponent.h"

#include <iostream>

dae::ScoreComponent::ScoreComponent(GameObject* parent) :
	Component(parent)
{
}

void dae::ScoreComponent::Update(float /*deltaTime*/)
{
}

void dae::ScoreComponent::Render() const
{
}

void dae::ScoreComponent::ChangeScore(int amount)
{
	m_Score += amount;
	std::cout << m_Score << "\n";
	NotifyObservers(GetParent(), Event::Points);
}
