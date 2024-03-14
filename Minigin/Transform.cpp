#include "Transform.h"

void dae::Transform::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3{ x,y,z });
}

void dae::Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}