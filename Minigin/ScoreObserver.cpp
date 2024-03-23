#include "ScoreObserver.h"

#include "GameObject.h"
#include "PlayerScoreComponent.h"
#include "TextComponent.h"

dae::ScoreObserver::ScoreObserver(GameObject* object) :
	m_pObject(object)
{

}

void dae::ScoreObserver::OnNotify(GameObject* object, const std::string& event) const
{
	if (event == "gainedPoints")
	{
		m_pObject->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(object->GetComponent<PlayerScoreComponent>()->GetScore()));
	}
}