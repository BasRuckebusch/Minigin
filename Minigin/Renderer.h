#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
		bool m_showDemo{ false };
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		void SetCameraPosition(const glm::vec2& position);

		void SetCameraScale(const float scale);

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
		SDL_Window* GetWindow() const { return m_window; }
		glm::vec2 GetCameraPosition() const { return m_cameraPosition; }
		float GetCameraScale() const { return m_cameraScale; }
	private:
		glm::vec2 m_cameraPosition{};
		float m_cameraScale{};
	};
}

