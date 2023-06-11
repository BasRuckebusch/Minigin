#pragma once
#include <Command.h>
#include <glm/vec2.hpp>

namespace dae
{
	class Scene;

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(GameObject* pGameObject, glm::vec2 direction) : m_Direction{ direction }, m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		glm::vec2 m_Direction{};
		GameObject* m_pGameObject;
	};

	class MoveLeftRight final : public Command
	{
	public:
		explicit MoveLeftRight(GameObject* pGameObject, bool MoveRight) : m_pGameObject(pGameObject), m_MoveRight(MoveRight) {}
		void Execute() override;
	private:
		GameObject* m_pGameObject;
		bool m_MoveRight;
	};

	class MoveUpDown final : public Command
	{
	public:
		explicit MoveUpDown(GameObject* pGameObject, bool MoveDown) : m_pGameObject(pGameObject), m_MoveDown(MoveDown) {}
		void Execute() override;
	private:
		GameObject* m_pGameObject;
		bool m_MoveDown;
	};

	class PlaceBomb final : public Command
	{
	public:
		explicit PlaceBomb(GameObject* pGameObject, Scene* pScene) : m_pGameObject(pGameObject), m_pScene(pScene) {}
		void Execute() override;
	private:
		GameObject* m_pGameObject;
		Scene* m_pScene;
	};
}

