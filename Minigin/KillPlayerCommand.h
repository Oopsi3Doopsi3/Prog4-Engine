#pragma once

#include "GameObjectCommand.h"
#include "PlayerHealthComponent.h"

namespace dae
{
	class KillPlayerCommand final : public GameObjectCommand
	{
	public:
		KillPlayerCommand(GameObject* object) :
			GameObjectCommand(object)
		{
		}

		void Execute() override
		{
			GetGameActor()->GetComponent<PlayerHealthComponent>()->Killed();
		}

	private:
	};
}