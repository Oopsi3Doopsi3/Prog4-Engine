#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* actor):
		m_pActor(actor)
		{
		}

		virtual ~GameActorCommand() = default;

	protected:
		GameObject* GetGameActor() const { return m_pActor; }

	private:
		GameObject* m_pActor;
	};
}
