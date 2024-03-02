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
		~GameObject();
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


		template<typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			m_pComponents.push_back(component);
			
			const auto pCastComponent{ static_cast<Component*>(component.get()) };
			pCastComponent->SetParent(this);
		}

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
		std::shared_ptr<T> GetComponent()
		{
			for (const auto& component : m_pComponents)
			{
				if (typeid(T) == typeid(*component)) {
				return std::dynamic_pointer_cast<T>(component);
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

		std::vector< std::shared_ptr<Component>> m_pComponents;

		std::shared_ptr<GameObject> m_Parent;
		std::vector<std::shared_ptr<GameObject>> m_Children;

		void AddChild(const std::shared_ptr<GameObject>& child);
		void UpdateWorldPosition();
	};
}
