#include "Transform.h"

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	SetPositionDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec3 pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::Transform::SetWorldPosition(const glm::vec3 pos)
{
	m_WorldPosition = pos;
}

void dae::Transform::SetPositionDirty()
{
	m_PositionIsDirty = true;
}

void dae::Transform::SetPositionClean()
{
	m_PositionIsDirty = false;
}