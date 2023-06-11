#pragma once

#include <memory>
#include <vector>
#include <glm/vec2.hpp>

#include "CollisionComponent.h"
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class CollisionManager final : public dae::Singleton<CollisionManager>
	{
	public:

		bool CheckPointInWall(const glm::vec2& point);
		bool CheckRectCollide(const SDL_Rect& col);

		std::vector<std::shared_ptr<GameObject>> AllBricksInRect(const SDL_Rect& rect);
		//std::vector<std::shared_ptr<GameObject>> AllBombsInRect(const SDL_Rect& rect, int tileSize);

		void AddWall(std::shared_ptr<GameObject> object);
		void RemoveWall(std::shared_ptr<GameObject> object);

		void AddBrick(std::shared_ptr<GameObject> object);
		void RemoveBrick(std::shared_ptr<GameObject> object);

		void AddBomb(std::shared_ptr<GameObject> object);
		void RemoveBomb(std::shared_ptr<GameObject> object);

		void AddPlayer(std::shared_ptr<GameObject> object);
		void RemovePlayer(std::shared_ptr<GameObject> object);

		void RemoveAll();

	private:
		std::vector<std::shared_ptr<GameObject>> m_pWalls{};
		std::vector<std::shared_ptr<GameObject>> m_pBricks{};
		std::vector<std::shared_ptr<GameObject>> m_pPlayers{};
		std::vector<std::shared_ptr<GameObject>> m_pBombs{};
	};
}
