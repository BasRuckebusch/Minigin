#pragma once
#include <memory>
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::string& filename, std::shared_ptr<GameObject> pParent);
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
