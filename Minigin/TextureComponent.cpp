#include "TextureComponent.h"
#include <string>
#include <utility>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent(const std::string& filename, std::shared_ptr<GameObject> pParent) :
	Component(pParent)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Update([[maybe_unused]] const float& deltaTime) { }

void dae::TextureComponent::Render() const
{
	const auto& pos = GetParent()->GetTransform()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
