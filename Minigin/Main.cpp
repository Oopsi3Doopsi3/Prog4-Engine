#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <Windows.h>
#include <Xinput.h>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureRenderComponent.h"
#include "FpsComponent.h"
#include "InputManager.h"
#include "RotatorComponent.h"
#include "MoveCommands.h"
#include "PlayerHealthComponent.h"
#include "KillPlayerCommand.h"
#include "HealthObserver.h"
#include "PlayerScoreComponent.h"
#include "ScoreObserver.h"
#include "AddPlayerScoreCommand.h"

using namespace dae;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	GameObject* background = scene.Add("Background");
	auto textureRenderer1 = new TextureRenderComponent(background);
	textureRenderer1->SetTexture("background.tga");
	background->AddComponent(textureRenderer1);
	
	GameObject* logo = scene.Add("Logo");
	auto textureRenderer2 = new TextureRenderComponent(logo);
	textureRenderer2->SetTexture("logo.tga");
	logo->AddComponent(textureRenderer2);
	logo->SetLocalPosition(216, 180, 0);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	GameObject* fps = scene.Add("Fps");
	auto textureRenderer5 = new TextureRenderComponent(fps);
	auto text3 = new TextComponent(fps, "Fps Counter", font);
	auto fpsComp = new FpsComponent(fps);
	fps->AddComponent(textureRenderer5);
	fps->AddComponent(text3);
	fps->AddComponent(fpsComp);
	fps->SetLocalPosition(5, 20, 0);

	///////////////////////////////
	//How To Play
	///////////////////////////////

	auto smallFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	GameObject* controllerExplanation = scene.Add("ControllerExplanation");
	auto controllerExplRend = new TextureRenderComponent(controllerExplanation);
	controllerExplanation->AddComponent(controllerExplRend);
	auto controllerExplText = new TextComponent(controllerExplanation, "Use the D-pad to move, X to inflict damage, A and B to gain points", smallFont);
	controllerExplanation->AddComponent(controllerExplText);
	controllerExplanation->SetLocalPosition(5, 70, 0);

	GameObject* keyboardExplanation = scene.Add("ControllerExplanation");
	auto keyboardExplRend = new TextureRenderComponent(keyboardExplanation);
	keyboardExplanation->AddComponent(keyboardExplRend);
	auto keyboardExplText = new TextComponent(keyboardExplanation, "Use the WASD to move, C to inflict damage, Z and X to gain points", smallFont);
	keyboardExplanation->AddComponent(keyboardExplText);
	keyboardExplanation->SetLocalPosition(5, 85, 0);

	///////////////////////////////
	//Player Ship Keyboard
	///////////////////////////////
	
	GameObject* keyboardLivesDisplay = scene.Add("KeyboardLivesDisplay");
	auto keyboardHealthObserver = new HealthObserver(keyboardLivesDisplay);

	GameObject* keyboardScoreDisplay = scene.Add("KeyboardScoreDisplay");
	auto keyboardScoreObserver = new ScoreObserver(keyboardScoreDisplay);
	
	//Ship
	GameObject* keyboardShip = scene.Add("KeyboardShip");
	auto keyboardHealth = new PlayerHealthComponent(keyboardShip);
	keyboardHealth->AddObserver(keyboardHealthObserver);
	keyboardShip->AddComponent(keyboardHealth);

	auto keyboardScore = new PlayerScoreComponent(keyboardShip);
	keyboardScore->AddObserver(keyboardScoreObserver);
	keyboardShip->AddComponent(keyboardScore);
	
	auto ship = new TextureRenderComponent(keyboardShip);
	ship->SetTexture("FighterShip2.png");
	keyboardShip->AddComponent(ship);

	keyboardShip->SetLocalPosition(180, 300, 0);

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_d,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(keyboardShip, glm::vec3{1,0,0}, 50.f));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_a,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(keyboardShip, glm::vec3{ -1,0,0 }, 50.f));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_w,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(keyboardShip, glm::vec3{ 0,-1,0 }, 50.f));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_s,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(keyboardShip, glm::vec3{ 0,1,0 }, 50.f));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_c,
		InputManager::KeyState::Pressed,
		std::make_unique<KillPlayerCommand>(keyboardShip));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_z,
		InputManager::KeyState::Pressed,
		std::make_unique<AddPlayerScoreCommand>(keyboardShip, 10));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_x,
		InputManager::KeyState::Pressed,
		std::make_unique<AddPlayerScoreCommand>(keyboardShip, 100));

	//Lives Display
	auto keyboardLivesDisplayRenderer = new TextureRenderComponent(keyboardLivesDisplay);
	keyboardLivesDisplay->AddComponent(keyboardLivesDisplayRenderer);

	auto keyboardLivesDisplayText = new TextComponent(keyboardLivesDisplay, "# lives: " + std::to_string(keyboardShip->GetComponent<PlayerHealthComponent>()->GetLives()), smallFont);
	keyboardLivesDisplay->AddComponent(keyboardLivesDisplayText);

	keyboardLivesDisplay->SetLocalPosition(5, 110, 0);

	//Score Display
	auto keyboardScoreDisplayRenderer = new TextureRenderComponent(keyboardScoreDisplay);
	keyboardScoreDisplay->AddComponent(keyboardScoreDisplayRenderer);

	auto keyboardScoreDisplayText = new TextComponent(keyboardScoreDisplay, "Score: " + std::to_string(keyboardShip->GetComponent<PlayerScoreComponent>()->GetScore()), smallFont);
	keyboardScoreDisplay->AddComponent(keyboardScoreDisplayText);

	keyboardScoreDisplay->SetLocalPosition(5, 130, 0);

	///////////////////////////////
	//Player Ship Controller
	///////////////////////////////
	GameObject* controllerLivesDisplay = scene.Add("ControllerLivesDisplay");
	auto controllerHealthObserver = new HealthObserver(controllerLivesDisplay);

	GameObject* controllerScoreDisplay = scene.Add("ControllerScoreDisplay");
	auto controllerScoreObserver = new ScoreObserver(controllerScoreDisplay);

	GameObject* controllerShip = scene.Add("ControllerShip");
	auto controllerHealth = new PlayerHealthComponent(controllerShip);
	controllerHealth->AddObserver(controllerHealthObserver);
	controllerShip->AddComponent(controllerHealth);

	auto controllerScore = new PlayerScoreComponent(controllerShip);
	controllerScore->AddObserver(controllerScoreObserver);
	controllerShip->AddComponent(controllerScore);

	auto ship2 = new TextureRenderComponent(controllerShip);
	ship2->SetTexture("FighterShip2.png");
	controllerShip->AddComponent(ship2);
	controllerShip->SetLocalPosition(200, 300, 0);
	
	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_RIGHT,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(controllerShip, glm::vec3{ 1,0,0 }, 100.f));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_LEFT,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(controllerShip, glm::vec3{ -1,0,0 }, 100.f));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_UP,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(controllerShip, glm::vec3{ 0,1,0 }, 100.f));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_DOWN,
		InputManager::KeyState::Down,
		std::make_unique<MoveCommand>(controllerShip, glm::vec3{ 0,-1,0 }, 100.f));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_X,
		InputManager::KeyState::Pressed,
		std::make_unique<KillPlayerCommand>(controllerShip));

	InputManager::GetInstance().AddKeyboardCommand(
		XINPUT_GAMEPAD_A,
		InputManager::KeyState::Pressed,
		std::make_unique<AddPlayerScoreCommand>(controllerShip, 10));

	InputManager::GetInstance().AddKeyboardCommand(
		XINPUT_GAMEPAD_B,
		InputManager::KeyState::Pressed,
		std::make_unique<AddPlayerScoreCommand>(controllerShip, 100));

	//Lives Display
	auto controllerLivesDisplayRenderer = new TextureRenderComponent(controllerLivesDisplay);
	controllerLivesDisplay->AddComponent(controllerLivesDisplayRenderer);

	auto controllerLivesDisplayText = new TextComponent(controllerLivesDisplay, "# lives: " + std::to_string(controllerShip->GetComponent<PlayerHealthComponent>()->GetLives()), smallFont);
	controllerLivesDisplay->AddComponent(controllerLivesDisplayText);

	controllerLivesDisplay->SetLocalPosition(5, 150, 0);

	//Score Display
	auto controllerScoreDisplayRenderer = new TextureRenderComponent(controllerScoreDisplay);
	controllerScoreDisplay->AddComponent(controllerScoreDisplayRenderer);

	auto controllerScoreDisplayText = new TextComponent(controllerScoreDisplay, "Score: " + std::to_string(controllerShip->GetComponent<PlayerScoreComponent>()->GetScore()), smallFont);
	controllerScoreDisplay->AddComponent(controllerScoreDisplayText);

	controllerScoreDisplay->SetLocalPosition(5, 170, 0);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}