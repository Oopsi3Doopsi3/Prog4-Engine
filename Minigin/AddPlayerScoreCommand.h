#pragma once

#include "GameObjectCommand.h"
#include "PlayerScoreComponent.h"

namespace dae
{
	class AddPlayerScoreCommand final : public GameObjectCommand
	{
	public:
		AddPlayerScoreCommand(GameObject* object, int score) :
			GameObjectCommand(object),
			m_Score(score)
		{
		}

		void Execute() override
		{
			GetGameActor()->GetComponent<PlayerScoreComponent>()->AddScore(m_Score);
		}

	private:
		int m_Score;
	};
}