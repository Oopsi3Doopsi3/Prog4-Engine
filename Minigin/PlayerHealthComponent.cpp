#include "PlayerHealthComponent.h"

#include "Observer.h"

dae::PlayerHealthComponent::PlayerHealthComponent(GameObject* owner):
	Component(owner)
{
	m_Subject = std::make_unique<Subject>();
}

void dae::PlayerHealthComponent::Killed()
{
	--m_Lives;
	m_Subject->NotifyObservers(GetOwnerObject(), "playerKilled");
}

void dae::PlayerHealthComponent::AddObserver(Observer* observer)
{
	m_Subject->AddObserver(observer);
}