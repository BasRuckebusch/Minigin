#include <SDL_rect.h>
#include "Component.h"

namespace dae
{
	class Scene;

	class BombComponent final : public Component
	{
	public:
		BombComponent(GameObject* parent, int tileSize, float fusetime, int range);
		~BombComponent() override = default;

		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

	private:
		int m_TileSize{ 16 };
		int m_Range{ 1 };
		float m_FuseTime{ 3 };
	};
}