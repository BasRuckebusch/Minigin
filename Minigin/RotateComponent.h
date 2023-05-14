#pragma once
#include "Component.h"

namespace dae
{
	class RotateComponent final : public Component
	{
	public:
		RotateComponent(GameObject* parent, float radius);
		~RotateComponent() override = default;

		RotateComponent(const RotateComponent& other) = delete;
		RotateComponent(RotateComponent&& other) = delete;
		RotateComponent& operator=(const RotateComponent& other) = delete;
		RotateComponent& operator=(RotateComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;
	private:
		float m_Angle{ 0.f };
		float m_Radius{ 1.f };
	};
}
