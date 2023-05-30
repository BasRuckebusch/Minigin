#include <glm/vec2.hpp>

namespace dae {
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute();
	};

	class MoveCommand final : public Command
	{
	public:
		explicit MoveCommand(GameObject* pGameObject, glm::vec2 direction) : m_Direction{ direction }, m_pGameObject(pGameObject) {}
		void Execute() override;
	private:
		glm::vec2 m_Direction{};
		GameObject* m_pGameObject;
	};
}
