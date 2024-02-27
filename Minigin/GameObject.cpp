#include "GameObject.h"

#include "ResourceManager.h"
#include "TextureRenderComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for(const auto& component : m_pComponents)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for(const auto& component : m_pComponents)
	{
		component->Render();
	}
}