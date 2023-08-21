#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Scene;

	class MenuComponent final : public Component
	{
	public:
		MenuComponent(GameObject* parent, const std::string& levelName, Scene* scene);
		~MenuComponent() override = default;

		MenuComponent(const MenuComponent& other) = delete;
		MenuComponent(MenuComponent&& other) = delete;
		MenuComponent& operator=(const MenuComponent& other) = delete;
		MenuComponent& operator=(MenuComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void Move(bool up);
		void Select() const;

	private:
		int m_GameMode{ 0 };
		std::string m_LevelName;
		Scene* m_pScene;
	};
}