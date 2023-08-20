#pragma once
namespace dae
{
	class GameObject;

	enum class Event
	{
		Points,
		Health,
		PlayerDie,
		GameOver
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject* actor, Event event) = 0;
	};
}
