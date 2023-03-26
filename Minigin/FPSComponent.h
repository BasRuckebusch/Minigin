#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(GameObject* parent);
		~FPSComponent() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

	private:
		TextComponent* m_pText{ nullptr };
		float m_Timer{};

		std::vector<int> averages;
	};
}
