#include "TextComponent.h"
#include <stdexcept>
#include <utility>

#include "Font.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font, const SDL_Color& color) :
	Component(nullptr),
	m_Color(color),
	m_Text(std::move(text)),
	m_Font(std::move(font))
{
}


dae::TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font) :
	TextComponent(std::move(text), std::move(font), SDL_Color(255,255,255))
{
}


void dae::TextComponent::Update([[maybe_unused]] float deltaTime)
{
	if (m_NeedsUpdate)
	{
		if (!m_pTexture) m_pTexture = m_pParent->GetComponent<TextureComponent>();

		if (m_pTexture)
		{
			m_pTexture->SetTexture(m_Font->GetFont(), m_Text.c_str(), m_Color);
			m_NeedsUpdate = false;
		}
	}
}

void dae::TextComponent::Render() const
{
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

