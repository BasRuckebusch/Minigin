#pragma once
#include "Component.h"

namespace dae
{
	class BoxColliderComponent;

	class EnemyComponent final : public Component
	{
	public:
		EnemyComponent(GameObject* parent);
		~EnemyComponent() override = default;

		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetDirection(glm::vec2 direction) { m_Direction = direction; }
		void PickNewDirection();

		bool CanMoveLeft() const;
		bool CanMoveRight() const;

	private:
		glm::ivec2 m_Direction{};

		float m_Speed {15};
		float m_XPos;
		float m_YPos;
		float m_DeltaTime{};

		bool m_HasKilled{false};

		BoxColliderComponent* m_GroundLeftCollider;
		BoxColliderComponent* m_GroundRightCollider;
	};
}