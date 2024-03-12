#pragma once
//#include "GameObject.h"

namespace dae
{
	class Transform;
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* owner) : m_pOwnerObject(owner) {}

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update();
		virtual void Render() const;

		GameObject* GetOwnerObject() const { return m_pOwnerObject; }
		Transform& GetTransform() const;

	private:
		GameObject* m_pOwnerObject;
	};

}