#pragma once
#include "Observer.h"

namespace dae
{
	class HealthObserver final : public Observer
	{
	public:
		HealthObserver(GameObject* object);

		void OnNotify(GameObject* object, const std::string& event) const override;

	private:
		GameObject* m_pObject;
	};
}
