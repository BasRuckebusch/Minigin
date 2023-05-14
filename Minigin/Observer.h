namespace dae
{
	class GameObject;

	enum class Event
	{
		PlayerDie
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject* actor, Event event) = 0;
	};
}