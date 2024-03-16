#include "MoveHorizontalComponent.h"
#include <glm/glm.hpp>

#include "GameObject.h"
#include "GameTime.h"

dae::MoveHorizontalComponent::MoveHorizontalComponent(GameObject* owner, float speed) :
	Component(owner),
	m_Speed(speed)
{
}

void dae::MoveHorizontalComponent::MoveHorizontal(int direction)
{
	const glm::vec3 movement{ m_Speed * GameTime::GetDeltaTime() * direction, 0, 0 };
	const glm::vec3 newPos{ GetOwnerObject()->GetLocalPosition() + movement };
	GetOwnerObject()->SetLocalPosition(newPos);
}