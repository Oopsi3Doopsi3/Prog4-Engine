#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Font;
	class TextureRenderComponent;

	class TextComponent : public Component
	{
	public:
		TextComponent(const std::string& text, std::shared_ptr<Font> font);

		void Update() override;

		void SetText(const std::string& text);
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<TextureRenderComponent> m_TextureRenderer;
	};
}
