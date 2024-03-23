#pragma once
#include "Component.h"

namespace dae
{
	class Subject;
	class Observer;

	class PlayerScoreComponent : public Component
	{
	public:
		PlayerScoreComponent(GameObject* owner);
		void AddScore(int score);
		void AddObserver(Observer* observer);

		int GetScore() const { return m_Score; }

	private:
		int m_Score{0};
		std::unique_ptr<Subject> m_Subject;
	};

}