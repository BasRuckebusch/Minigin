#include "ScoreComponent.h"

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
	NotifyObservers(GetParent(), Event::Points);
}
