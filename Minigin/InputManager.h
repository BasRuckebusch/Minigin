#pragma once
#include "Singleton.h"
#include <vector>
#include <map>
#include <memory>
#include <unordered_set>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

namespace dae
{
	class Command;
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() override;

		bool ProcessInput();
		bool IsPressed(WORD button) const;
		void BindCommand(WORD button, Command* command);
		void AddPlayer(GameObject* player);
	private:
		XINPUT_STATE m_CurrentState{};
		int m_DeadZone = 7000;

		std::vector<GameObject*>m_pPlayers{};
		std::map<WORD, Command*> m_KeyMap;
		std::unordered_set<WORD> m_PressedKeys;

		class impl;
		std::unique_ptr<impl> pimpl;
	};

}
