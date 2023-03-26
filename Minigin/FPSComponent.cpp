#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(GameObject* parent):
	Component(parent)
{
}

dae::FPSComponent::~FPSComponent()
= default;

void dae::FPSComponent::Update(float deltaTime)
{
	if (!m_pText) m_pText = GetParent()->GetComponent<TextComponent>();

	int fps = static_cast<int>(1.f / deltaTime);

	if (m_pText)
	{
		m_Timer += deltaTime;
		if (m_Timer >= 0.1f)
		{
			averages.push_back(fps);
			if (averages.size()>1000)
			{
				averages.pop_back();
			}
			int sum{ 0 };
			for (int average : averages)
			{
				sum += average;
			}
			fps = static_cast<int>(sum / averages.size());
			m_pText->SetText(std::to_string(fps));
			m_Timer = 0.f;
		}
	}

}

void dae::FPSComponent::Render() const
{
	Component::Render();
}
