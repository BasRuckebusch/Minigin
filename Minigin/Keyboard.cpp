#include "Keyboard.h"

#include <iostream>
#include <string>

using namespace dae;

class Keyboard::impl
{
public:
	impl();

	void Update();

	static bool IsDown(SDL_Keycode key);
	bool IsUp(SDL_Keycode key) const;
	bool IsPressed(SDL_Keycode key) const;

private:
	const Uint8* m_CurrentState;
	Uint8 m_PreviousState[SDL_NUM_SCANCODES]{};
};

Keyboard::Keyboard()
	: pImpl{ std::make_unique<impl>() }
{
}

dae::Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	pImpl->Update();
}

bool Keyboard::IsDown(SDL_Keycode key) const
{
	return pImpl->IsDown(key);
}

bool Keyboard::IsUp(SDL_Keycode key) const
{
	return pImpl->IsUp(key);
}

bool Keyboard::IsPressed(SDL_Keycode key) const
{
	return pImpl->IsPressed(key);
}

Keyboard::impl::impl()
{
	m_CurrentState = SDL_GetKeyboardState(nullptr);
	SDL_memset(m_PreviousState, 0, sizeof(m_PreviousState));
}

void Keyboard::impl::Update()
{
	SDL_memcpy(m_PreviousState, m_CurrentState, sizeof(m_PreviousState));
	m_CurrentState = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::impl::IsDown(SDL_Keycode key)
{
	const Uint8* scancodeState = SDL_GetKeyboardState(nullptr);
	const SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return scancodeState[scancode];
}

bool Keyboard::impl::IsUp(SDL_Keycode key) const
{
	const SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return m_PreviousState[scancode] && !m_CurrentState[scancode];
}

bool Keyboard::impl::IsPressed(SDL_Keycode key) const
{
	const SDL_Scancode scancode = SDL_GetScancodeFromKey(key);
	return m_PreviousState[scancode] && IsDown(key);
}