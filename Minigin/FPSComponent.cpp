#include "FPSComponent.h"

#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent():
	Component(nullptr)
{
}

dae::FPSComponent::~FPSComponent()
= default;

void dae::FPSComponent::Update(const float& deltaTime)
{
	if (!m_pText) m_pText = m_pParent->GetComponent<TextComponent>();

	const int fps = static_cast<int>(1.f / deltaTime);

	if (m_pText)
	{
		m_Timer += deltaTime;
		if (m_Timer >= 0.5f)
		{
			m_pText->SetText(std::to_string(fps));
			m_Timer = 0.f;
		}
	}

}

void dae::FPSComponent::Render() const
{
	Component::Render();
}
