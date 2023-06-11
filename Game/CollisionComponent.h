#pragma once
#include <SDL_rect.h>
#include "Component.h"

namespace dae
{
	class CollisionComponent final : public Component
	{
	public:
		CollisionComponent(GameObject* parent, const SDL_Rect& rect);
		CollisionComponent(GameObject* parent, const glm::vec2& pos, int width, int height);
		~CollisionComponent() override = default;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;
		

		SDL_Rect GetRect() const { return m_Rect; }
		void SetPosition(const glm::vec2& pos) 
		{
			m_Rect.x = static_cast<int>(pos.x + m_Offset.x);
			m_Rect.y = static_cast<int>(pos.y + m_Offset.y);
		}
		void SetOffset(const glm::vec2& offset)
		{
			m_Offset.x = offset.x;
			m_Offset.y = offset.y;
		}

		//bool DoesCollide(const CollisionComponent* other) const;
		bool DoesCollide(const SDL_Rect& other) const;
		bool PointInCollider(const glm::vec2& point);
		
	private:
		SDL_Rect m_Rect{};
		glm::vec2 m_Offset{};
	};
}