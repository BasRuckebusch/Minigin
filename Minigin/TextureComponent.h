#pragma once
#include <memory>
#include <SDL_pixels.h>
#include <SDL_ttf.h>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::string& filename);
		TextureComponent();
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(TTF_Font* font, const char* text, SDL_Color color);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
