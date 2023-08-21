#pragma once
#include "Component.h"

namespace dae
{
	class TitleComponent final : public Component
	{
	public:
		TitleComponent(GameObject* parent);
		~TitleComponent() override = default;

		TitleComponent(const TitleComponent& other) = delete;
		TitleComponent(TitleComponent&& other) = delete;
		TitleComponent& operator=(const TitleComponent& other) = delete;
		TitleComponent& operator=(TitleComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

	private:
		float m_XPos;
		float m_YPos;
		float m_Amplitude{ 5 };
		float m_Frequency{ 1 };
		float m_Timer{};
	};
}