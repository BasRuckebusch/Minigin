#include "Gamepad.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

using namespace dae;

class Gamepad::impl
{
public:
	explicit impl(unsigned int index);

	void Update();

	bool IsDown(unsigned int button) const;
	bool IsUp(unsigned int button) const;
	bool IsPressed(unsigned int button) const;

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	WORD m_ButtonPressed{};
	WORD m_ButtonReleased{};

	unsigned int m_Index{ 0 };
};

Gamepad::Gamepad(unsigned int index)
	: pImpl{ std::make_unique<impl>(index) }
{
}

dae::Gamepad::~Gamepad()
{
}

void Gamepad::Update() const
{
	pImpl->Update();
}

bool Gamepad::IsDown(ControllerButton button) const
{
	return pImpl->IsDown(static_cast<unsigned int>(button));
}

bool Gamepad::IsUp(ControllerButton button) const
{
	return pImpl->IsUp(static_cast<unsigned int>(button));
}

bool Gamepad::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

Gamepad::impl::impl(unsigned int index)
	: m_Index(index)
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
}


void Gamepad::impl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_Index, &m_CurrentState);

	// Bitmask of changes between current and previous states
	const int changedButtonsMask = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	// Bitmask of newly pressed buttons 
	m_ButtonPressed = changedButtonsMask & m_CurrentState.Gamepad.wButtons;
	// Bitmask of newly released buttons 
	m_ButtonReleased = changedButtonsMask & (~m_CurrentState.Gamepad.wButtons);
}

bool Gamepad::impl::IsDown(const unsigned int button) const
{
	return m_ButtonPressed & static_cast<int>(button);
}

bool Gamepad::impl::IsUp(const unsigned int button) const
{
	return m_ButtonReleased & static_cast<int>(button);
}

bool Gamepad::impl::IsPressed(const unsigned int button) const
{
	return m_CurrentState.Gamepad.wButtons & static_cast<int>(button);
}