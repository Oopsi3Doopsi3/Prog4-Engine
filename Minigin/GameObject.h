#pragma once
#include <memory>
#include "Transform.h"
#include <vector>

namespace dae
{
	class Component;

	class GameObject final
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

		template<typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			auto component = std::make_shared<T>(std::forward<Args>(args)...);
			m_pComponents.push_back(component);
			
			const auto pCastComponent{ static_cast<Component*>(component.get()) };
			pCastComponent->m_pParentObject = this;
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

		Transform& GetTransform() { return m_Transform; }
	private:
		Transform m_Transform{};
		std::vector<std::shared_ptr<Component>> m_pComponents;
	};
}