#include <vector>
#include "Observer.h"

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
	protected:
		void NotifyObservers(GameObject* go, Event event);
	private:
		std::vector<Observer*> m_pObservers;
	};
}

