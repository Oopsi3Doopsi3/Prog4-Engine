#pragma once
#include "Component.h"

namespace dae
{
	class MoveVerticalComponent final : public Component
	{
	public:
		MoveVerticalComponent(GameObject* owner, float speed);

		void MoveVertical(int direction);

	private:
		const float m_Speed;
	};
}