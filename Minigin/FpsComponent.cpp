#include "FpsComponent.h"

#include <sstream>
#include "TextComponent.h"
#include "GameTime.h"
#include "GameObject.h"

void dae::FpsComponent::Update()
{
	if(m_TextComponent == nullptr)
		m_TextComponent = GetOwnerObject()->GetComponent<TextComponent>();

	std::stringstream text;
	text << std::fixed << std::setprecision(1) << GameTime::GetAverageFps() << " FPS";

	m_TextComponent->SetText(text.str());
}
