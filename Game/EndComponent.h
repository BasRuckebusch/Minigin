#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Scene;

	class EndComponent final : public Component
	{
	public:
		EndComponent(GameObject* parent, Scene* pScene, std::vector<std::string> levelNames);
		~EndComponent() override = default;

		EndComponent(const EndComponent& other) = delete;
		EndComponent(EndComponent&& other) = delete;
		EndComponent& operator=(const EndComponent& other) = delete;
		EndComponent& operator=(EndComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

	private:
		Scene* m_pScene{};
		std::vector<std::string> m_LevelNames{};
		bool m_Ended{false};
	};
}