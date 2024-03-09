#include "RotatorComponent.h"

#include "GameTime.h"

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3& rotationCenter):
Component(owner),
m_RotationCenter(rotationCenter),
m_TargetPos(rotationCenter)
{
}

void dae::RotatorComponent::Update()
{
	constexpr float speed{ 100.f };
	constexpr float radius{ 30.f };

	m_TargetPos += glm::vec3(std::cos(dae::GameTime::GetDeltaTime() * speed) * radius,
		std::sin(dae::GameTime::GetDeltaTime() * speed) * radius, 0);

	Transform().SetLocalPosition(m_TargetPos);
}
