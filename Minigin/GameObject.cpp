#include "GameObject.h"

#include "ResourceManager.h"
#include "TextureRenderComponent.h"

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

void dae::GameObject::AddComponent(Component* component)
{
	m_pComponents.emplace_back(component);
}

void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent.get() == this || m_Parent == parent)
		return;

	if (parent == nullptr)
		m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() - m_Parent->GetTransform().GetWorldPosition());
		m_Transform.SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(shared_from_this());
	m_Parent = parent;
	if (m_Parent) m_Parent->m_Children.emplace_back(this);
}

bool dae::GameObject::IsChild(const std::shared_ptr<GameObject>& potentialChild) const
{
	for(const auto& child : m_Children)
	{
		if (child == potentialChild)
			return true;
	}
	return false;
}

void dae::GameObject::RemoveChild(const std::shared_ptr<GameObject>& child)
{
	for(auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		if(*it == child)
		{
			m_Children.erase(it);
			return;
		}
	}
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_Transform.GetPositionIsDirty())
		UpdateWorldPosition();
	return m_Transform.GetWorldPosition();
}

void dae::GameObject::UpdateWorldPosition()
{
	if(m_Transform.GetPositionIsDirty())
	{
		if (m_Parent == nullptr)
			m_Transform.SetWorldPosition(m_Transform.GetLocalPosition());
		else
			m_Transform.SetWorldPosition(m_Parent->GetWorldPosition() + m_Transform.GetLocalPosition());
	}
	m_Transform.SetPositionClean();
}