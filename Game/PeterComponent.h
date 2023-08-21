#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class BoxColliderComponent;
	class Scene;

	class PeterComponent final : public Component
	{
	public:
		PeterComponent(GameObject* parent, bool isEvil, Scene* scene, std::string levelName);
		~PeterComponent() override = default;

		PeterComponent(const PeterComponent& other) = delete;
		PeterComponent(PeterComponent&& other) = delete;
		PeterComponent& operator=(const PeterComponent& other) = delete;
		PeterComponent& operator=(PeterComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		bool IsOnLadder() const;
		bool CanMoveDown() const;
		bool CanMoveUp() const;
		bool CanMoveLeft() const;
		bool CanMoveRight() const;

		void Die();
	private:
		bool m_IsOnLadder{false};
		bool m_isOnGround{ false };
		bool m_IsEvil{ false };
		bool m_Dead{ false };

		Scene* m_pScene{};
		std::string m_LevelName{};

		BoxColliderComponent* m_LeftCollider;
		BoxColliderComponent* m_RightCollider;
		BoxColliderComponent* m_DownCollider;
		BoxColliderComponent* m_UpCollider;
		BoxColliderComponent* m_GroundLeftCollider;
		BoxColliderComponent* m_GroundRightCollider;

	};
}