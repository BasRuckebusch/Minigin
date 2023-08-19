#pragma once

#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "BoxColliderComponent.h"
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class CollisionManager final : public dae::Singleton<CollisionManager>
	{
	public:
		bool IsCollidingWithLadder(const SDL_Rect& col) const;

		void AddLadder(std::shared_ptr<GameObject> object);
		void RemoveLadder(std::shared_ptr<GameObject> object);

		//void AddEnemy(std::shared_ptr<GameObject> object);
		//void RemoveEnemy(std::shared_ptr<GameObject> object);

		void RemoveAll();

	private:
		std::vector<std::shared_ptr<GameObject>> m_pLadders{};
	};
}
