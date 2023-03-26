#pragma once
#include <glm/glm.hpp>

namespace dae {
	class GameObject;

	class Command
	{
	public:
		Command() {};
		virtual ~Command() {}
		virtual void Execute(GameObject& actor) = 0;
	protected:
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
