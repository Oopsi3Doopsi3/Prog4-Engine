#include "PlayerScoreComponent.h"

#include "Observer.h"

dae::PlayerScoreComponent::PlayerScoreComponent(GameObject* owner):
	Component(owner)
{
	m_Subject = std::make_unique<Subject>();
}

void dae::PlayerScoreComponent::AddScore(int score)
{
	m_Score += score;
	m_Subject->NotifyObservers(GetOwnerObject(), "gainedPoints");
}

void dae::PlayerScoreComponent::AddObserver(Observer* observer)
{
	m_Subject->AddObserver(observer);
}