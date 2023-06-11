#include "CollisionComponent.h"

#include "Renderer.h"

dae::CollisionComponent::CollisionComponent(GameObject* parent, const SDL_Rect& rect) :
	Component(parent),
	m_Rect{ rect }
{
}

dae::CollisionComponent::CollisionComponent(GameObject* parent, const glm::vec2& pos, int width, int height) :
	Component(parent)
{
	m_Rect = SDL_Rect{ static_cast<int>(pos.x), static_cast<int>(pos.y), width, height };
}

void dae::CollisionComponent::Update(float)
{
}

void dae::CollisionComponent::Render() const
{
	auto renderer = dae::Renderer::GetInstance().GetSDLRenderer();
	SDL_SetRenderDrawColor(renderer, Uint8{ 255 }, Uint8{ 0 }, Uint8{ 0 }, Uint8{ 255 });
}

bool dae::CollisionComponent::DoesCollide(const SDL_Rect& other) const
{
	return SDL_HasIntersection(&m_Rect, &other);
}

bool dae::CollisionComponent::PointInCollider(const glm::vec2& point)
{
	const SDL_Point p{ static_cast<int>(point.x), static_cast<int>(point.y) };
	return SDL_PointInRect(&p, &m_Rect);
}
