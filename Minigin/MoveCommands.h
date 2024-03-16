#pragma once
#include "GameActorCommand.h"

namespace dae
{
	class MoveHorizontalCommand final : public GameActorCommand
	{
	public:
		MoveHorizontalCommand(GameObject* actor, int direction):
			GameActorCommand(actor),
			m_Direction(direction)
		{
			m_pMoveComponent = GetGameActor()->GetComponent<MoveHorizontalComponent>();
		}

		void Execute() override
		{
			m_pMoveComponent->MoveHorizontal(m_Direction);
		}

	private:
		MoveHorizontalComponent* m_pMoveComponent;
		int m_Direction;
	};

	class MoveVerticalCommand final : public GameActorCommand
	{
	public:
		MoveVerticalCommand(GameObject* actor, int direction) :
			GameActorCommand(actor),
			m_Direction(direction)
		{
			m_pMoveComponent = GetGameActor()->GetComponent<MoveVerticalComponent>();
		}

		void Execute() override
		{
			m_pMoveComponent->MoveVertical(m_Direction);
		}
	private:
		MoveVerticalComponent* m_pMoveComponent;
		int m_Direction;
	};
}
