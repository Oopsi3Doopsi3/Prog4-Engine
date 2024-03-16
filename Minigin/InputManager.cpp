#include <SDL.h>
#include "InputManager.h"

#include "backends/imgui_impl_sdl2.h"

#include <Windows.h>
#include <Xinput.h>

class dae::InputManager::ControllerInputImpl
{
public:
	void AddCommand(unsigned int button, KeyState state, std::unique_ptr<GameActorCommand> actorCommand)
	{
		m_ControllerCommands.emplace_back(InputCommand{ button, state, std::move(actorCommand)});
	}

	void ProcessInput()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);

		const auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		const auto buttonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		const auto buttonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		for(const auto& command : m_ControllerCommands)
		{
			switch(command.state)
			{
			case KeyState::Pressed:
				if (buttonsPressedThisFrame & command.button)
					command.command->Execute();
				break;
			case KeyState::Up:
				if (buttonsReleasedThisFrame & command.button)
					command.command->Execute();
				break;
			case KeyState::Down:
				if (m_CurrentState.Gamepad.wButtons & command.button)
					command.command->Execute();
				break;
			}
		}
	}

private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	std::vector<InputCommand> m_ControllerCommands;
};

dae::InputManager::InputManager():
	m_pControllerInputImpl(new ControllerInputImpl{})
{
}

dae::InputManager::~InputManager()
{
	delete m_pControllerInputImpl;
}

void dae::InputManager::AddControllerCommand(unsigned int button, KeyState state, std::unique_ptr<GameActorCommand> actorCommand)
{
	m_pControllerInputImpl->AddCommand(button, state, std::move(actorCommand));
}

void dae::InputManager::AddKeyboardCommand(unsigned int button, KeyState state, std::unique_ptr<GameActorCommand> actorCommand)
{
	m_KeyboardCommands.emplace_back(InputCommand{ button, state, std::move(actorCommand) });
}

bool dae::InputManager::ProcessInput()
{
	//Controller
	m_pControllerInputImpl->ProcessInput();

	//Keyboard
	m_PreviousStateKeyboard = m_CurrentStateKeyboard;
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_CurrentStateKeyboard[e.key.keysym.sym] = true;
		}
		if (e.type == SDL_KEYUP) {
			m_CurrentStateKeyboard[e.key.keysym.sym] = false;
		}

		//IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	for(const auto& command : m_KeyboardCommands)
	{
		const bool buttonChangedThisFrame{ m_CurrentStateKeyboard[command.button] != m_PreviousStateKeyboard[command.button] };

		switch(command.state)
		{
		case KeyState::Pressed:
			if (buttonChangedThisFrame && m_CurrentStateKeyboard[command.button])
				command.command->Execute();
			break;
		case KeyState::Up:
			if (buttonChangedThisFrame && !m_CurrentStateKeyboard[command.button])
				command.command->Execute();
			break;
		case KeyState::Down:
			if (m_CurrentStateKeyboard[command.button])
				command.command->Execute();
			break;
		}
	}

	return true;
}