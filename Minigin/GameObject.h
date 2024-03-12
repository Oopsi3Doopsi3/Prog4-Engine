#pragma once
#include <list>
#include <memory>
#include <string>

#include "Transform.h"
#include <vector>
#include "Component.h"

namespace dae
{
	class Component;

	class GameObject final
	{
	public:
		GameObject(const std::string& name);

		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		Transform& GetTransform() { return m_Transform; }
		const glm::vec3& GetWorldPosition();
		void SetParent(GameObject* parent, bool keepWorldPosition);
		
		

		void AddComponent(Component* component);

		template<typename T>
		void RemoveComponent()
		{
			for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
			{
				if (typeid(T) == typeid(*(*it))) {
					m_pComponents.erase(it);
					return;
				}
			}
		}

		template<typename  ComponentType>
		requires std::derived_from<ComponentType, Component>
		ComponentType* GetComponent()
		{
			for(const auto& component : m_pComponents)
			{
				if(typeid(ComponentType) == typeid(*component))
				{
					return dynamic_cast<ComponentType*>(component.get());
				}
			}
			return nullptr;
		}

		template<typename ComponentType>
		requires std::derived_from<ComponentType, Component>
		bool HasComponent() const
		{
			for (const auto& component : m_pComponents)
			{
				if (typeid(ComponentType) == typeid(*component)) {
					return true;
				}
			}
			return false;
		}

	private:
		std::string m_Name;
		Transform m_Transform{};

		//std::vector<Component*> m_pComponents{};
		std::list<std::unique_ptr<Component>> m_pComponents;

		GameObject* m_Parent;
		std::vector<GameObject*> m_Children{};

		void UpdateWorldPosition();

		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		bool IsChild(GameObject* child) const;
	};
}
