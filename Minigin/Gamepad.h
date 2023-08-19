#pragma once
#include <memory>

namespace dae
{
	enum class ControllerButton
	{
		LeftStick = 0x0040,
		RightStick = 0x0080,

		Up = 0x0001,
		Down = 0x0002,
		Left = 0x0004,
		Right = 0x0008,

		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,

		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,

		Start = 0x0010,
		Select = 0x0020,
	};

	class Gamepad final
	{
	public:

		explicit Gamepad(unsigned int index);
		~Gamepad();

		void Update() const;

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
	private:
		class impl;
		std::unique_ptr<impl> pImpl;
	};
}
