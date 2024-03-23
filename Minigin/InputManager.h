#pragma once
#include <map>

#include "Singleton.h"
#include "GameObjectCommand.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class KeyState
		{
			Pressed,
			Up,
			Down
		};

		struct InputCommand
		{
			unsigned int button;
			KeyState state;
			std::unique_ptr<GameObjectCommand> command;
		};

		InputManager();
		virtual ~InputManager() override;

		void AddControllerCommand(unsigned int button, KeyState state, std::unique_ptr<GameObjectCommand> actorCommand);
		void AddKeyboardCommand(unsigned int button, KeyState state, std::unique_ptr<GameObjectCommand> actorCommand);

		bool ProcessInput();

	private:

		class ControllerInputImpl;
		ControllerInputImpl* m_pControllerInputImpl{};

		std::vector<InputCommand> m_KeyboardCommands;
		std::map<int, bool> m_PreviousStateKeyboard;
		std::map<int, bool> m_CurrentStateKeyboard;
	};
}
