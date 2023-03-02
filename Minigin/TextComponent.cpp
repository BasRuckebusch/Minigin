#include "TextComponent.h"
#include <stdexcept>
#include <utility>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color) :
	Component(nullptr),
	m_Color(color),
	m_Text(text),
	m_Font(std::move(font)),
	m_TextTexture(nullptr)
{
}

dae::TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font) :
	TextComponent(text, std::move(font), SDL_Color(255,255,255))
{
}


void dae::TextComponent::Update([[maybe_unused]] const float& deltaTime)
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
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
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	if (m_TextTexture != nullptr)
	{
		const auto& pos = m_pParent->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_TextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::TextComponent::SetColor(const Uint8& r, const Uint8& g, const Uint8& b)
{
	m_Color = SDL_Color(r, g, b);
}

