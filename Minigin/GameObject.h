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

		const std::string& GetName() const { return m_Name; }

		void Update();
		void Render() const;
		void LateUpdate();

		void SetParent(GameObject* parent, bool keepWorldPosition);

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void SetLocalPosition(float x, float y, float z);
		void SetLocalPosition(const glm::vec3& position);
		void SetPositionDirty();
		
		void MarkDestroy() { m_MarkedDestroy = true; }
		bool GetMarkedDestroy() const { return m_MarkedDestroy; }

		void AddComponent(Component* component);
		void DestroyComponents();

		template<typename ComponentType>
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
		void RemoveComponent()
		{
			GetComponent<ComponentType>()->MarkDestroy();
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
		bool m_MarkedDestroy{};

		//Transform
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		bool m_PositionDirty{ false };

		//Components
		std::list<std::unique_ptr<Component>> m_pComponents;

		//Children
		GameObject* m_Parent;
		std::vector<GameObject*> m_Children{};

		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		bool IsChild(GameObject* child) const;

		void UpdateWorldPosition();
	};
}
