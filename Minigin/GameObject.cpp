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

		if (auto intPlot = dynamic_cast<PlotComponent*>(component.get()))
		{
			intPlot->RenderPlot();
		}
	}
}

void dae::GameObject::LateUpdate()
{
	
}


/////////////////
///Components
/////////////////

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


/////////////////
///Children
/////////////////

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (parent == this || m_Parent == parent || IsChild(parent))
		return;

	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - m_Parent->GetWorldPosition());
		SetPositionDirty();
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


/////////////////
///Position
/////////////////

const glm::vec3& dae::GameObject::GetLocalPosition() const
{
	return m_LocalTransform.GetPosition();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionDirty)
		UpdateWorldPosition();
	return m_WorldTransform.GetPosition();
}

void dae::GameObject::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition(glm::vec3{ x, y, z });
}

void dae::GameObject::SetLocalPosition(const glm::vec3& position)
{
	m_LocalTransform.SetPosition(position);
	SetPositionDirty();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (!m_PositionDirty)
		return;
	
	if (m_Parent == nullptr)
		m_WorldTransform.SetPosition(GetLocalPosition());
	else
		m_WorldTransform.SetPosition(m_Parent->GetWorldPosition() + GetLocalPosition());
	
	m_PositionDirty = false;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionDirty = true;
	for (const auto& child : m_Children)
	{
		child->SetPositionDirty();
	}
}