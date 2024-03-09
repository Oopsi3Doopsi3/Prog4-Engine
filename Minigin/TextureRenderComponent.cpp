#include "TextureRenderComponent.h"

#include "Renderer.h"
#include "ResourceManager.h"

void dae::TextureRenderComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = GetOwnerObject()->GetWorldPosition();
		//const auto& pos = GetTransform().GetLocalPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextureRenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureRenderComponent::SetTexture(const std::shared_ptr<dae::Texture2D>& texture)
{
	m_Texture = texture;
}
