#pragma once
#include "Singleton.h"
#include <windows.h>
#include <XInput.h>

#include "GameObject.h"
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddPlayer(GameObject* player);
	private:
		XINPUT_STATE m_CurrentState{};
		int m_DeadZone = 7000;

		std::vector<GameObject*>m_pPlayers{};
	};

}
