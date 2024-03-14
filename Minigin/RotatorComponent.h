#pragma once
#include <glm/vec3.hpp>

#include "Component.h"

namespace dae
{
	class RotatorComponent : public Component
	{
	public:
		RotatorComponent(GameObject* owner, const glm::vec3& rotationCenter);

		void Update() override;

	private:
		glm::vec3 m_RotationCenter;
		float m_Angle;
	};
}

