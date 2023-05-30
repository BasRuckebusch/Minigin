#include "InputManager.h"
#include <SDL.h>
#include <backends/imgui_impl_sdl2.h>
#include <iostream>
#include "Command.h"

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	if (IsPressed(XINPUT_GAMEPAD_DPAD_LEFT))
	{
		MoveLeftRight move{ m_pPlayers[0], false };
		move.Execute();
	}
	if (IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT))
	{
		MoveLeftRight move{ m_pPlayers[0], true };
		move.Execute();
	}
	if (IsPressed(XINPUT_GAMEPAD_DPAD_UP))
	{
		MoveUpDown move{ m_pPlayers[0], false };
		move.Execute();
	}
	if (IsPressed(XINPUT_GAMEPAD_DPAD_DOWN))
	{
		MoveUpDown move{ m_pPlayers[0], true };
		move.Execute();
	}

	//	glm::vec2 direction{ 0.f, 0.f };
	//	if (IsPressed(XINPUT_GAMEPAD_DPAD_UP) || m_CurrentState.Gamepad.sThumbLY > m_DeadZone)
	//	{
	//		direction.y--;
	//	}
	//	if (IsPressed(XINPUT_GAMEPAD_DPAD_DOWN) || m_CurrentState.Gamepad.sThumbLY < -m_DeadZone)
	//	{
	//		direction.y++;
	//	}
	//	if (IsPressed(XINPUT_GAMEPAD_DPAD_LEFT) || m_CurrentState.Gamepad.sThumbLX < -m_DeadZone)
	//	{
	//		direction.x--;
	//	}
	//	if (IsPressed(XINPUT_GAMEPAD_DPAD_RIGHT) || m_CurrentState.Gamepad.sThumbLX > m_DeadZone)
	//	{
	//		direction.x++;
	//	}
	//	
	//	if (m_pPlayers[0] != nullptr)
	//	{
	//		MoveCommand move{m_pPlayers[0], direction };
	//		move.Execute();
	//	}
	//	
	//	direction = { 0.f, 0.f };
	//	SDL_Event e;
	//	while (SDL_PollEvent(&e)) {
	//		if (e.type == SDL_QUIT) {
	//			return false;
	//		}
	//		if (e.type == SDL_KEYDOWN) {
	//			switch (e.key.keysym.sym)
	//			{
	//			case SDLK_w:
	//				direction.y--;
	//				break;
	//			case SDLK_s:
	//				direction.y++;
	//				break;
	//			case SDLK_a:
	//				direction.x--;
	//				break;
	//			case SDLK_d:
	//				direction.x++;
	//				break;
	//			}
	//		}
	//		if (e.type == SDL_MOUSEBUTTONDOWN) {
	//			
	//		}
	//		//process event for IMGUI
	//		ImGui_ImplSDL2_ProcessEvent(&e);
	//	}
	//	
	//	if (m_pPlayers[1] != nullptr)
	//	{
	//		MoveCommand move{ m_pPlayers[1], direction };
	//		move.Execute();
	//	}

	return true;
}

bool dae::InputManager::IsPressed(int button) const
{
	return ((m_CurrentState.Gamepad.wButtons & button) != 0);
}

void dae::InputManager::AddPlayer(GameObject* player)
{
	m_pPlayers.emplace_back(player);
}