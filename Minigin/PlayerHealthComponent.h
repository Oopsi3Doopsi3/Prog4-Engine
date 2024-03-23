#pragma once
#include "Component.h"

namespace dae
{
	class Subject;
	class Observer;

	class PlayerHealthComponent : public Component
	{
	public:
		PlayerHealthComponent(GameObject* owner);
		void Killed();
		void AddObserver(Observer* observer);

		int GetLives() const { return m_Lives; }

	private:
		int m_Lives{ 3 };
		std::unique_ptr<Subject> m_Subject;
	};
}
