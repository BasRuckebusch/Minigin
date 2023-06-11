#pragma once
#include "Component.h"

namespace dae
{
	class Scene;

	class BomberManComponent final : public Component
	{
	public:
		BomberManComponent(GameObject* parent, int tileSize);
		~BomberManComponent() override = default;

		BomberManComponent(const BomberManComponent& other) = delete;
		BomberManComponent(BomberManComponent&& other) = delete;
		BomberManComponent& operator=(const BomberManComponent& other) = delete;
		BomberManComponent& operator=(BomberManComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void PlaceBomb(Scene* scene);

	private:
		int m_TileSize{16};
	};
}