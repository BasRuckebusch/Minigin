#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include "Command.h"

class dae::InputManager::impl
{
	public:
		bool ProcessInput()
		{
			ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
			XInputGetState(0, &m_CurrentState);

			for (auto i = m_KeyMap.begin(); i != m_KeyMap.end(); ++i)
			{
				WORD k = i->first;
				if (IsPressed(k)) m_KeyMap[k]->Execute();
			}

			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					return false;
				}
				if (e.type == SDL_KEYDOWN) {
					WORD key = static_cast<WORD>(e.key.keysym.sym);
					m_PressedKeys.insert(key);
				}
				if (e.type == SDL_KEYUP)
				{
					WORD key = static_cast<WORD>(e.key.keysym.sym);
					m_PressedKeys.erase(key);
				}
				if (e.type == SDL_MOUSEBUTTONDOWN) {

				}
				//process event for IMGUI
				ImGui_ImplSDL2_ProcessEvent(&e);
			}

			for (const auto& key : m_PressedKeys)
			{
				Command* Command = m_KeyMap[key];
				if (Command)
					Command->Execute();
			}

			return true;
		}

		bool IsPressed(WORD button)
		{
			return (m_CurrentState.Gamepad.wButtons & button) != 0;
		}

		void BindCommand(WORD button, Command* command)
		{
			m_KeyMap[button] = command;
		}
	private:
		XINPUT_STATE m_CurrentState{};

		std::map<WORD, Command*> m_KeyMap;
		std::unordered_set<WORD> m_PressedKeys;
};

dae::InputManager::InputManager()
	: pimpl{ std::make_unique<impl>() }
{
}

dae::InputManager::~InputManager()
{
	for (auto command : m_KeyMap)
	{
		delete command.second;
		command.second = nullptr;
	}
}

bool dae::InputManager::ProcessInput()
{
	return pimpl->ProcessInput();
}

bool dae::InputManager::IsPressed(WORD button) const
{
	return pimpl->IsPressed(button);
}

void dae::InputManager::BindCommand(WORD button, Command* command)
{
	pimpl->BindCommand(button, command);
}

void dae::InputManager::AddPlayer(GameObject* player)
{
	m_pPlayers.emplace_back(player);
}
