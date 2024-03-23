#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject* actor):
		m_pActor(actor)
		{
		}

		virtual ~GameObjectCommand() = default;

	protected:
		GameObject* GetGameActor() const { return m_pActor; }

	private:
		GameObject* m_pActor;
	};
}
