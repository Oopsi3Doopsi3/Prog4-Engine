#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureRenderComponent : public Component
	{
	public:
		TextureRenderComponent(GameObject* owner) : Component(owner) {}

		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<dae::Texture2D>& texture);

	private:
		std::shared_ptr<dae::Texture2D> m_Texture;
	};
}


