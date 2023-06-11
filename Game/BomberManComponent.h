#pragma once
#include <string>
#include "Component.h"

namespace dae
{
	class Scene;

	class BomberManComponent final : public Component
	{
	public:
		BomberManComponent(GameObject* parent, Scene* scene, int tileSize);
		~BomberManComponent() override = default;

		BomberManComponent(const BomberManComponent& other) = delete;
		BomberManComponent(BomberManComponent&& other) = delete;
		BomberManComponent& operator=(const BomberManComponent& other) = delete;
		BomberManComponent& operator=(BomberManComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void PlaceBomb();
		void GiveBomb();
		void Die();
		void SetLevelName(const std::string& levelName) { m_LevelName = levelName; }

	private:
		int m_TileSize{ 16 };
		Scene* m_pScene{};
		std::string m_LevelName{};
		bool m_Dead{ false };
		float m_BombTimer{ 0.7f };
		float m_BombElapsed{ m_BombTimer };
		int m_Bombs{0};
		int m_MaxBombs{1};
		float m_Fuse{2.f};
		int m_Range{1};
	};
}