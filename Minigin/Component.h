#pragma once
#include "GameObject.h"

namespace dae
{
	class Transform;

	class Component
	{
		friend class GameObject;

	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update();
		virtual void Render() const;
		
	protected:
		Component() = default;

		GameObject* GetParentObject() const { return m_pParentObject; }
		Transform GetTransform() const { return m_pParentObject->GetTransform(); }

	private:
		GameObject* m_pParentObject;
		void SetParent(GameObject* parent);
	};

}

