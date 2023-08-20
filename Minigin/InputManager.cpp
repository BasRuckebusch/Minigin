#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include "Command.h"


dae::InputManager::InputManager()
{
	m_pControllers.push_back(std::make_unique<Gamepad>(0));
	m_pKeyboard = std::make_unique<Keyboard>();
}

dae::InputManager::~InputManager()
= default;

bool dae::InputManager::ProcessInput() const
{
	for (const auto& controller : m_pControllers)
	{
		for (const auto& entry : m_ControllerMap)
		{
			const auto& button = entry.first;
			const auto& commandPair = entry.second;
			const auto& command = commandPair.first;
			const auto& eventState = commandPair.second;

			switch (eventState)
			{
			case EventState::keyPressed: 
				if (controller->IsPressed(button))
					command->Execute();
				break;
			case EventState::keyUp:
				if (controller->IsUp(button))
					command->Execute();
				break;
			case EventState::keyDown:
				if (controller->IsDown(button))
					command->Execute();
				break;
			}
		}
		controller->Update();
	}

	if (m_pKeyboard)
	{
		for (const auto& entry : m_KeyMap)
		{
			const auto& keyCode = entry.first;
			const auto& commandPair = entry.second;
			const auto& command = commandPair.first;
			const auto& eventState = commandPair.second;

			switch (eventState)
			{
			case EventState::keyPressed:
				if (m_pKeyboard->IsPressed(keyCode))
					command->Execute();
				break;
			case EventState::keyUp:
				if (m_pKeyboard->IsUp(keyCode))
					command->Execute();
				break;
			case EventState::keyDown:
				if (m_pKeyboard->IsDown(keyCode))
					command->Execute();
				break;
			}
		}
		m_pKeyboard->Update();
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		// Process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;

}

void dae::InputManager::BindCommand(ControllerButton button, std::unique_ptr<Command> command, EventState inputType)
{
	// Create a pair of command and input type
	std::pair commandPair(std::move(command), inputType);
	// Insert the entry into the m_ControllerMap
	m_ControllerMap[button] = std::move(commandPair);
}

void dae::InputManager::BindCommand(SDL_Keycode key, std::unique_ptr<Command> command, EventState inputType)
{
	std::pair commandPair(std::move(command), inputType);
	m_KeyMap[key] = std::move(commandPair);
}