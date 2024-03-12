#include "GameObject.h"

#include "ResourceManager.h"
#include "PlotComponent.h"

dae::GameObject::GameObject(const std::string& name):
m_Name(name),
m_Parent(nullptr)
{
	
}

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

		//if (PlotComponent* intPlot = dynamic_cast<PlotComponent*>(component))
		//{
		//	intPlot->RenderPlot();
		//}
	}
}

void dae::GameObject::LateUpdate()
{
	
}

void dae::GameObject::AddComponent(Component* component)
{
	m_pComponents.emplace_back(component);
}

void dae::GameObject::DestroyComponents()
{
	m_pComponents.erase(
		std::remove_if(
			m_pComponents.begin(),
			m_pComponents.end(),
			[](const std::unique_ptr<Component>& component) {return component->GetMarkedDestroy(); }
		),
		m_pComponents.end()
	);
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent)
		return;

	if (parent == nullptr)
		m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetWorldPosition() - m_Parent->GetTransform().GetWorldPosition());
		m_Transform.SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

bool dae::GameObject::IsChild(GameObject* child) const
{
	const auto found = std::ranges::find(m_Children, child);
	return found != m_Children.end();
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase(m_Children, child);
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
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