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
            if (IsPressed(k))
                m_KeyMap[k]->Execute();
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                return false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                WORD key = static_cast<WORD>(e.key.keysym.sym);
                m_PressedKeys.insert(key);
            }
            if (e.type == SDL_KEYUP)
            {
                WORD key = static_cast<WORD>(e.key.keysym.sym);
                m_PressedKeys.erase(key);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
            }
            // Process event for IMGUI
            ImGui_ImplSDL2_ProcessEvent(&e);
        }

        for (const auto& key : m_PressedKeys)
        {
            auto command = m_KeyMap[key].get();
            if (command)
                command->Execute();
        }

        return true;
    }

    bool IsPressed(WORD button)
    {
        return (m_CurrentState.Gamepad.wButtons & button) != 0;
    }

    void BindCommand(WORD button, std::unique_ptr<Command> command)
    {
        m_KeyMap[button] = std::move(command);
    }

private:
    XINPUT_STATE m_CurrentState{};
    std::map<WORD, std::unique_ptr<Command>> m_KeyMap;
    std::unordered_set<WORD> m_PressedKeys;
};

dae::InputManager::InputManager()
    : pimpl{ std::make_unique<impl>() }
{
}

dae::InputManager::~InputManager()
{
}

bool dae::InputManager::ProcessInput()
{
    return pimpl->ProcessInput();
}

bool dae::InputManager::IsPressed(WORD button) const
{
    return pimpl->IsPressed(button);
}

void dae::InputManager::BindCommand(WORD button, std::unique_ptr<Command> command)
{
    pimpl->BindCommand(button, std::move(command));
}
