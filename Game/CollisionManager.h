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
		void CollideWithIngredients(const SDL_Rect& col) const;

		void ChainFall(GameObject* parent, const SDL_Rect& col) const;
		void InPot(GameObject* parent, const SDL_Rect& col);

		void AddLadder(std::shared_ptr<GameObject> object);
		void RemoveLadder(std::shared_ptr<GameObject> object);

		void AddIngredient(std::shared_ptr<GameObject> object);
		void RemoveIngredient(std::shared_ptr<GameObject> object);

		void AddStopper(std::shared_ptr<GameObject> object);
		void RemoveStopper(std::shared_ptr<GameObject> object);

		void AddPot(std::shared_ptr<GameObject> object);
		void RemovePot(std::shared_ptr<GameObject> object);

		int GetAmountPots() const { return static_cast<int>(m_pPots.size()/2 - m_FilledPots); }
		//int GetAmountPots() const { return 0; }


		//void AddEnemy(std::shared_ptr<GameObject> object);
		//void RemoveEnemy(std::shared_ptr<GameObject> object);

		void RemoveAll();
		

	private:
		int m_FilledPots{};
		std::vector<std::shared_ptr<GameObject>> m_pLadders{};
		std::vector<std::shared_ptr<GameObject>> m_pIngredients{};
		std::vector<std::shared_ptr<GameObject>> m_pStoppers{};
		std::vector<std::shared_ptr<GameObject>> m_pPots{};
	};
}
