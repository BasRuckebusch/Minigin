#pragma once
#include "Component.h"

namespace dae
{
	class MoveComponent final : public Component
	{
	public:
		MoveComponent(GameObject* parent);
		~MoveComponent() override = default;

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void Move(glm::vec2 direction);

	private:
		glm::vec2 m_Direction{};

		float m_Speed {50};
		float m_XPos;
		float m_YPos;
		float m_DeltaTime{};
	};
}