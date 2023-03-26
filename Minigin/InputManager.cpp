#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include "Command.h"


bool IsPressed(const XINPUT_GAMEPAD& gamepad, int button)
{
	return ((gamepad.wButtons & button) != 0);
}

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	glm::vec2 direction{ 0.f, 0.f };
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_UP) || m_CurrentState.Gamepad.sThumbLY > m_DeadZone)
	{
		direction.y--;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_DOWN) || m_CurrentState.Gamepad.sThumbLY < -m_DeadZone)
	{
		direction.y++;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_LEFT) || m_CurrentState.Gamepad.sThumbLX < -m_DeadZone)
	{
		direction.x--;
	}
	if (IsPressed(m_CurrentState.Gamepad, XINPUT_GAMEPAD_DPAD_RIGHT) || m_CurrentState.Gamepad.sThumbLX > m_DeadZone)
	{
		direction.x++;
	}

	MoveCommand move{ direction };
	if (m_pPlayers[0] != nullptr)
	{
		move.Execute(*m_pPlayers[0]);
	}

	direction = { 0.f, 0.f };
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
				direction.y--;
				break;
			case SDLK_s:
				direction.y++;
				break;
			case SDLK_a:
				direction.x--;
				break;
			case SDLK_d:
				direction.x++;
				break;
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		//process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	MoveCommand move2{ direction };
	if (m_pPlayers[1] != nullptr)
	{
		move2.Execute(*m_pPlayers[1]);
	}

	return true;
}

void dae::InputManager::AddPlayer(GameObject* player)
{
	m_pPlayers.emplace_back(player);
}