#pragma once
#include <memory>
#include <string>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(const std::string& filename);
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
