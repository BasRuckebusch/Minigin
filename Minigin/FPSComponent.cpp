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
