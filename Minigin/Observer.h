#pragma once
#include <string>
#include <vector>
#include <memory>

namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(GameObject* object, const std::string& event) const = 0;
	};

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(const Observer* observer);
		void ResetObservers();
		void NotifyObservers(GameObject* object, const std::string& event) const;

	private:
		std::vector<std::unique_ptr<Observer>> m_Observers;
	};
}
