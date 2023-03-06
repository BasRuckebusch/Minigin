#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <string>

#include "Component.h"


namespace dae
{
	class Font;
	class Texture2D;
	class TextureComponent;

	class TextComponent final : public Component
	{
	public:
		TextComponent(std::string text, std::shared_ptr<Font> font);
		TextComponent(std::string text, std::shared_ptr<Font> font, const SDL_Color& color);
		~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetColor(const Uint8& r, const Uint8& g, const Uint8& b);
	private:
		bool m_NeedsUpdate{true};
		SDL_Color m_Color {255,255,255};
		std::string m_Text{" "};
		std::shared_ptr<Font> m_Font;
		TextureComponent* m_pTexture{ nullptr };
	};
}
