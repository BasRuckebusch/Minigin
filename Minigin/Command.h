#pragma once
#include <glm/glm.hpp>

namespace dae {
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute();
		virtual void Execute(GameObject& actor);
	};

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(glm::vec2 direction) : m_Direction{ direction } {}
		void Execute(GameObject& actor) override;
	private:
		glm::vec2 m_Direction{};
	};
}
