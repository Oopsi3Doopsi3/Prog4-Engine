#include "Component.h"
#include "GameObject.h"

void dae::Component::Update()
{
	
}

void dae::Component::Render() const
{
	
}

dae::Transform& dae::Component::GetTransform() const
{
	return m_pOwnerObject->GetTransform();
}