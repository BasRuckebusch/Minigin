#include "ScoreUIComponent.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

dae::ScoreUIComponent::ScoreUIComponent(GameObject* parent) :
	Component(parent)
{
	
}

void dae::ScoreUIComponent::Update(float)
{
	if (!m_pText) m_pText = GetParent()->GetComponent<TextComponent>();
}

void dae::ScoreUIComponent::Render() const
{
}

void dae::ScoreUIComponent::Notify(const GameObject* actor, Event events)
{
	switch (events)
	{
	case Event::Points:
		const int score = actor->GetComponent<ScoreComponent>()->GetScore();
		m_pText->SetText("Points: " + std::to_string(score));
		break;
	}
}