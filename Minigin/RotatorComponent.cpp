#include "RotatorComponent.h"

#include "GameTime.h"
#include "GameObject.h"
#include <SDL_stdinc.h>

dae::RotatorComponent::RotatorComponent(GameObject* owner, const glm::vec3& rotationCenter):
Component(owner),
m_RotationCenter(rotationCenter),
m_Angle(0.f)
{
}

void dae::RotatorComponent::Update()
{
	constexpr float speed{ 3.f };
	constexpr float radius{ 30.f };
	
	constexpr float completeRotation{ 2.f * static_cast<float>(M_PI) };

	m_Angle += GameTime::GetDeltaTime() * speed;

	if (m_Angle > completeRotation)
		m_Angle -= completeRotation;

	const glm::vec3 position = m_RotationCenter + glm::vec3{ glm::cos(m_Angle) * radius, glm::sin(m_Angle) * radius, 0.f };

	GetOwnerObject()->SetLocalPosition(position);
}
