#pragma once
#include "Component.h"

namespace dae
{
	class MoveHorizontalComponent final : public Component
	{
	public:
		MoveHorizontalComponent(GameObject* owner, float speed);

		void MoveHorizontal(int direction);

	private:
		const float m_Speed;
	};
}

