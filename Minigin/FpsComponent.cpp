#include "FpsComponent.h"

#include <sstream>
#include "TextComponent.h"
#include "GameTime.h"

void dae::FpsComponent::Update()
{
	if(m_TextComponent == nullptr)
		m_TextComponent = GetParentObject()->GetComponent<TextComponent>();

	std::stringstream text;
	text << std::fixed << std::setprecision(1) << GameTime::GetAverageFps() << " FPS";

	std::shared_ptr<TextComponent> textComponent = GetParentObject()->GetComponent<TextComponent>();
	m_TextComponent->SetText(text.str());
}
