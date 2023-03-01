#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pParent);
		~FPSComponent() override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

	private:
		TextComponent* m_pText{ nullptr };
		float m_Timer{};
	};
}