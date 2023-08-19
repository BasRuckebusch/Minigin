#pragma once
#include <memory>
#include <SDL.h>

namespace dae
{
	class Keyboard final
	{
	public:
		Keyboard();
		~Keyboard();

		void Update();

		bool IsDown(SDL_Keycode key) const;
		bool IsUp(SDL_Keycode key) const;
		bool IsPressed(SDL_Keycode key) const;

	private:
		class impl;
		std::unique_ptr<impl> pImpl;
	};
}