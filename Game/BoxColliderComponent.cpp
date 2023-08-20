#include "BoxColliderComponent.h"

#include "Renderer.h"

dae::BoxColliderComponent::BoxColliderComponent(GameObject* parent, const SDL_Rect& rect) :
	Component(parent),
	m_Rect{ rect }
{
}

dae::BoxColliderComponent::BoxColliderComponent(GameObject* parent, const glm::vec2& pos, int width, int height) :
	Component(parent)
{
	m_Rect = SDL_Rect{ static_cast<int>(pos.x), static_cast<int>(pos.y), width, height };
}

void dae::BoxColliderComponent::Update(float)
{
}

void dae::BoxColliderComponent::Render() const
{
	// SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);
	// SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
}

void dae::BoxColliderComponent::SetPosition(const glm::vec2& pos)
{
	m_Rect.x = static_cast<int>(pos.x + m_Offset.x);
	m_Rect.y = static_cast<int>(pos.y + m_Offset.y);
}

void dae::BoxColliderComponent::SetOffset(const glm::vec2& offset)
{
	m_Offset.x = offset.x;
	m_Offset.y = offset.y;

	m_Rect.x = static_cast<int>(m_Rect.x + m_Offset.x);
	m_Rect.y = static_cast<int>(m_Rect.y + m_Offset.y);
}

bool dae::BoxColliderComponent::RectInCollider(const SDL_Rect& other) const
{
	return SDL_HasIntersection(&m_Rect, &other);
}

bool dae::BoxColliderComponent::PointInCollider(const glm::vec2& point) const
{
	const SDL_Point p{ static_cast<int>(point.x), static_cast<int>(point.y) };
	return SDL_PointInRect(&p, &m_Rect);
}
