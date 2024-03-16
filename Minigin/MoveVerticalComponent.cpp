#include "MoveVerticalComponent.h"

#include <glm/glm.hpp>

#include "GameObject.h"
#include "GameTime.h"

dae::MoveVerticalComponent::MoveVerticalComponent(GameObject* owner, float speed):
	Component(owner),
	m_Speed(speed)
{
}

void dae::MoveVerticalComponent::MoveVertical(int direction)
{
	const glm::vec3 movement{ 0, m_Speed * GameTime::GetDeltaTime() * -direction, 0 };
	const glm::vec3 newPos{ GetOwnerObject()->GetLocalPosition() + movement };
	GetOwnerObject()->SetLocalPosition(newPos);
}