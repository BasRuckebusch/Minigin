#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	for (auto o : m_pObservers)
		if (observer == o)
			std::erase(m_pObservers, o);
}

void dae::Subject::NotifyObservers(GameObject* go, Event event)
{
	for (auto observer : m_pObservers)
		observer->Notify(go, event);
}
