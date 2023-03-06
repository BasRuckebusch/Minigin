#include "TextureComponent.h"

#include <stdexcept>
#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"

dae::TextureComponent::TextureComponent(const std::string& filename) :
	Component(nullptr)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

dae::TextureComponent::TextureComponent() :
	Component(nullptr)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture("missing.tga");
}

void dae::TextureComponent::Update([[maybe_unused]] float deltaTime) {  }

void dae::TextureComponent::Render() const
{
	const auto& pos = m_pParent->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(TTF_Font* font, const char* text, SDL_Color color)
{
	const auto surf = TTF_RenderText_Blended(font, text, color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_Texture = std::make_shared<Texture2D>(texture);
}
