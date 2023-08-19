#pragma once
#include <SDL_rect.h>
#include "Component.h"

namespace dae
{
	class BoxColliderComponent final : public Component
	{
	public:
		BoxColliderComponent(GameObject* parent, const SDL_Rect& rect);
		BoxColliderComponent(GameObject* parent, const glm::vec2& pos, int width, int height);
		~BoxColliderComponent() override = default;

		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;
		

		SDL_Rect GetRect() const { return m_Rect; }
		void SetPosition(const glm::vec2& pos);
		void SetOffset(const glm::vec2& offset);

		//bool RectInCollider(const BoxColliderComponent* other) const;
		bool RectInCollider(const SDL_Rect& other) const;
		bool PointInCollider(const glm::vec2& point) const;
		
	private:
		SDL_Rect m_Rect{};
		glm::vec2 m_Offset{};
	};
}