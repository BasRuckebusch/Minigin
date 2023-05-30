#pragma once
#include "Singleton.h"
#include <vector>
#include <map>
#include <memory>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

namespace dae
{
	class GameObject;
	class Command;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager() override;

		bool ProcessInput();
		bool IsPressed(int button) const;
		void AddPlayer(GameObject* player);
	private:
		XINPUT_STATE m_CurrentState{};
		int m_DeadZone = 7000;

		std::vector<GameObject*>m_pPlayers{};
	};

}
