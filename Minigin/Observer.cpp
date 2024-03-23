#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(const Observer* observer)
{
	for (size_t i = 0; i < m_Observers.size(); ++i)
	{
		if (m_Observers[i].get() == observer)
		{
			m_Observers.erase(m_Observers.begin() + i);
			return;
		}
	}
}

void dae::Subject::ResetObservers()
{
	m_Observers.clear();
}

void dae::Subject::NotifyObservers(GameObject* object, const std::string& event) const
{
	for(const auto& observer : m_Observers)
	{
		observer->OnNotify(object, event);
	}
}
