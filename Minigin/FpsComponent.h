#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FpsComponent : public Component
	{
	public:
		void Update() override;

	private:
		std::shared_ptr<TextComponent> m_TextComponent;
	};
}