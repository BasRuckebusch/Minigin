#include "CameraComponent.h"
#include "Renderer.h"

dae::CameraComponent::CameraComponent(GameObject* parent) :
	Component(parent)
{
	auto& pos = GetParent()->GetWorldPosition();
	auto& renderer = Renderer::GetInstance();
	SDL_GetWindowSize(renderer.GetWindow(), &m_Width, &m_Height);
	renderer.SetCameraPosition({ pos.x- m_Width *.5f, pos.y- m_Height * .5f });
}

void dae::CameraComponent::Update(float)
{

}

void dae::CameraComponent::Render() const
{
	auto& pos = GetParent()->GetWorldPosition();
	auto& renderer = Renderer::GetInstance();
	renderer.SetCameraPosition({ pos.x - (m_Width*.5f)/ renderer.GetCameraScale() +16 , pos.y - (m_Height * .5f) / renderer.GetCameraScale() + 16 });
}