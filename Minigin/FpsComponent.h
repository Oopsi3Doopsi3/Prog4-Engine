#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FpsComponent : public Component
	{
	public:
		FpsComponent(GameObject* owner) : Component(owner) {}

		void Update() override;

	private:
		TextComponent* m_TextComponent;
	};
}