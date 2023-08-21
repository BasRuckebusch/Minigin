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

	class MenuMove final : public Command
	{
	public:
		explicit MenuMove(GameObject* pGameObject, bool up) : m_Up{ up }, m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		bool m_Up{};
		GameObject* m_pGameObject;
	};

	class MenuSelect final : public Command
	{
	public:
		explicit MenuSelect(GameObject* pGameObject) : m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		GameObject* m_pGameObject;
	};

	class NextLevel final : public Command
	{
	public:
		explicit NextLevel(Scene* pScene, std::vector<std::string> levelNames ) : m_pScene(pScene), m_LevelNames(std::move(levelNames)) {}
		void Execute() override;
	private:
		Scene* m_pScene;
		int m_Id{};
		std::vector<std::string> m_LevelNames{};
	};

	class MenuLoad final : public Command
	{
	public:
		explicit MenuLoad(Scene* pScene, const std::string& levelName) : m_pScene(pScene), m_LevelName(levelName){}
		void Execute() override;
	private:
		Scene* m_pScene;
		std::string m_LevelName{};
		std::vector<std::string> m_LevelNames{};
	};

	class PauseMusic final : public Command
	{
	public:
		explicit PauseMusic() = default;
		void Execute() override;
	};

	class StopSound final : public Command
	{
	public:
		explicit StopSound() = default;
		void Execute() override;
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