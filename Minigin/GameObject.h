#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

namespace dae
{
	class Component;

	class GameObject final : std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void Render() const;

		Transform& GetTransform() { return m_Transform; }
		const glm::vec3& GetWorldPosition();
		void SetParent(const std::shared_ptr<GameObject>& parent, bool keepWorldPosition);
		bool IsChild(const std::shared_ptr<GameObject>& potentialChild) const;
		void RemoveChild(const std::shared_ptr<GameObject>& child);

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

		template<typename T>
		T* GetComponent()
		{
			for (const auto& component : m_pComponents)
			{
				if (typeid(T) == typeid(*component)) {
				return dynamic_cast<T*>(component);
				}
			}
			return nullptr;
		}

		template<typename T>
		bool HasComponent() const
		{
			for (const auto& component : m_pComponents)
			{
				if (typeid(T) == typeid(*component)) {
					return true;
				}
			}
			return false;
		}

	private:
		Transform m_Transform{};

		std::vector<Component*> m_pComponents;

		std::shared_ptr<GameObject> m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;

		void UpdateWorldPosition();
	};
}
