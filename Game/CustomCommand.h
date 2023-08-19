#pragma once
#include <Command.h>
#include <string>
#include <vector>
#include <glm/vec2.hpp>

namespace dae
{
	class Scene;

	class Move final : public Command
	{
	public:
		explicit Move(GameObject* pGameObject, glm::vec2 direction) : m_Direction{ direction }, m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		glm::vec2 m_Direction{};
		GameObject* m_pGameObject;
	};

	class PlaceBomb final : public Command
	{
	public:
		explicit PlaceBomb(GameObject* pGameObject) : m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		GameObject* m_pGameObject;
	};

	class NextLevel final : public Command
	{
	public:
		explicit NextLevel(Scene* pScene, std::vector<std::string> levelNames ) : m_pScene(pScene), m_LevelNames(
			std::move(levelNames)){}
		void Execute() override;
	private:
		Scene* m_pScene;
		int m_Id{};
		std::vector<std::string> m_LevelNames{};
	};

	class LevelLoad final : public Command
	{
	public:
		explicit LevelLoad(Scene* pScene, const std::string& levelName) : m_pScene(pScene), m_LevelName(levelName) {}
		void Execute() override;
	private:
		Scene* m_pScene;
		std::string m_LevelName{};
	};
}

