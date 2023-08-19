#pragma once
#include <memory>
#include <map>
#include <vector>

#include "Gamepad.h"
#include "Keyboard.h"
#include "Command.h"
#include "Singleton.h"

namespace dae
{
	enum class EventState
	{
		keyPressed,
		keyUp,
		keyDown
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() override;

		bool ProcessInput() const;
		void BindCommand(ControllerButton button, std::unique_ptr<Command> command, EventState inputType);
		void BindCommand(SDL_Keycode key, std::unique_ptr<Command> command, EventState inputType);

	private:
		EventState m_EventState{};
		std::vector< std::unique_ptr<Gamepad>> m_pControllers;
		std::map<ControllerButton, std::pair<std::unique_ptr<Command>, EventState>> m_ControllerMap;
		std::unique_ptr<Keyboard> m_pKeyboard;
		std::map<SDL_Keycode, std::pair<std::unique_ptr<Command>, EventState>> m_KeyMap;
	};
}
