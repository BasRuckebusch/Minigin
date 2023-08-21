#pragma once
#include "TitleComponent.h"
dae::TitleComponent::TitleComponent(GameObject* parent) :
	Component(parent)
{
	auto& pos = GetParent()->GetLocalPosition();
	m_XPos = pos.x;
	m_YPos = pos.y;
}

void dae::TitleComponent::Update(float deltaTime)
{
	float newYPos = m_YPos + m_Amplitude * std::sin(m_Frequency * m_Timer);
	m_Timer += deltaTime;

	GetParent()->SetLocalPosition({ m_XPos, newYPos , 0 });
}

void dae::TitleComponent::Render() const
{
}