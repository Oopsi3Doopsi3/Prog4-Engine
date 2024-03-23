#include "HealthObserver.h"

#include "GameObject.h"
#include "PlayerHealthComponent.h"
#include "TextComponent.h"

dae::HealthObserver::HealthObserver(GameObject* object):
	m_pObject(object)
{
	
}

void dae::HealthObserver::OnNotify(GameObject* object, const std::string& event) const
{
	if (event == "playerKilled")
	{
		m_pObject->GetComponent<TextComponent>()->SetText("# lives: " + std::to_string(object->GetComponent<PlayerHealthComponent>()->GetLives()));
	}
}
