#pragma once
#include "Component.h"

namespace dae
{
	class CameraComponent final : public Component
	{
	public:
		CameraComponent(GameObject* parent);
		~CameraComponent() override = default;

		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetBoundaries(const glm::vec2& boundaries) { m_XBoundaries = boundaries; }

	private:
		int m_Width{};
		int m_Height{};
		glm::vec2 m_XBoundaries{};
		//Rectf m_Boundaries;

		glm::vec2 Track(const glm::vec3& target) const;
		void Clamp() const;
	};
}
