#pragma once
#include "GameObjectCommand.h"
#include "GameTime.h"

namespace dae
{
	class MoveCommand final : public GameObjectCommand
	{
	public:
		MoveCommand(GameObject* object,const glm::vec3& direction, float speed):
		GameObjectCommand(object),
		m_Direction(direction),
		m_Speed(speed)
		{
		}

		void Execute() override
		{
			glm::vec3 movement = m_Direction * m_Speed * dae::GameTime::GetDeltaTime();
			glm::vec3 newPos = GetGameActor()->GetLocalPosition() + movement;
			GetGameActor()->SetLocalPosition(newPos);
		}

	private:
		glm::vec3 m_Direction;
		float m_Speed;
	};
}
