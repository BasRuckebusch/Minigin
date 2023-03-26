#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include "Command.h"


bool IsButtonAPressed(const XINPUT_GAMEPAD& gamepad)
{
	return ((gamepad.wButtons & XINPUT_GAMEPAD_A) != 0);
}

bool IsPressed(const XINPUT_GAMEPAD& gamepad, int button)
{
	return ((gamepad.wButtons & button) != 0);
}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	glm::vec2 direction{ 0.f, 0.f };

	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_UP))
	{
		direction.y--;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_DOWN))
	{
		direction.y++;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_LEFT))
	{
		direction.x--;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		direction.x++;
	}

	MoveCommand move{ direction };
	if (m_pPlayers[0] != nullptr)
	{
		move.Execute(*m_pPlayers[0]);
	}
	

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::AddPlayer(GameObject* player)
{
	m_pPlayers.emplace_back(player);
}