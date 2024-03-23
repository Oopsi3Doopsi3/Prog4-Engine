#pragma once
#include "Observer.h"

namespace dae
{
	class ScoreObserver: public Observer
	{
	public:
		ScoreObserver(GameObject* object);

		void OnNotify(GameObject* object, const std::string& event) const override;

	private:
		GameObject* m_pObject;
	};
}