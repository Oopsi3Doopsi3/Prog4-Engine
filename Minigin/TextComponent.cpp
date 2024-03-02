#include "TextComponent.h"

#include <SDL_ttf.h>
#include <stdexcept>
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TextureRenderComponent.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	: m_Text(text), m_Font(std::move(font))
{}

void dae::TextComponent::Update()
{
	if(m_TextureRenderer == nullptr)
		m_TextureRenderer = GetParentObject()->GetComponent<TextureRenderComponent>();

	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		
		m_TextureRenderer->SetTexture(std::make_shared<Texture2D>(texture));
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}