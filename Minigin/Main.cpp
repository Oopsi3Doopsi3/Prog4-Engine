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
#include "PlotComponent.h"
#include "MoveVerticalComponent.h"
#include "MoveHorizontalComponent.h"
#include "MoveCommands.h"

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

	GameObject* keyboardShip = scene.Add("keyboardShipp");
	auto ship = new TextureRenderComponent(keyboardShip);
	ship->SetTexture("FighterShip2.png");
	auto moveVertical1 = new MoveVerticalComponent(keyboardShip, 50.f);
	auto moveHorizontal1 = new MoveHorizontalComponent(keyboardShip, 50.f);
	keyboardShip->AddComponent(ship);
	keyboardShip->SetLocalPosition(180, 300, 0);
	keyboardShip->AddComponent(moveVertical1);
	keyboardShip->AddComponent(moveHorizontal1);

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_d,
		InputManager::KeyState::Down,
		std::make_unique<MoveHorizontalCommand>(keyboardShip, 1));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_a,
		InputManager::KeyState::Down,
		std::make_unique<MoveHorizontalCommand>(keyboardShip, -1));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_w,
		InputManager::KeyState::Down,
		std::make_unique<MoveVerticalCommand>(keyboardShip, 1));

	InputManager::GetInstance().AddKeyboardCommand(
		SDLK_s,
		InputManager::KeyState::Down,
		std::make_unique<MoveVerticalCommand>(keyboardShip, -1));

	GameObject* controllerShip = scene.Add("controllerShip");
	auto ship2 = new TextureRenderComponent(controllerShip);
	ship2->SetTexture("FighterShip2.png");
	auto moveVertical2 = new MoveVerticalComponent(controllerShip, 100.f);
	auto moveHorizontal2 = new MoveHorizontalComponent(controllerShip, 100.f);
	controllerShip->AddComponent(ship2);
	controllerShip->SetLocalPosition(200, 300, 0);
	controllerShip->AddComponent(moveVertical2);
	controllerShip->AddComponent(moveHorizontal2);

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_RIGHT,
		InputManager::KeyState::Down,
		std::make_unique<MoveHorizontalCommand>(controllerShip, 1));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_LEFT,
		InputManager::KeyState::Down,
		std::make_unique<MoveHorizontalCommand>(controllerShip, -1));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_UP,
		InputManager::KeyState::Down,
		std::make_unique<MoveVerticalCommand>(controllerShip, 1));

	InputManager::GetInstance().AddControllerCommand(
		XINPUT_GAMEPAD_DPAD_DOWN,
		InputManager::KeyState::Down,
		std::make_unique<MoveVerticalCommand>(controllerShip, -1));
	
	//dae::GameObject* go = scene.Add("Graph");
	//auto plot = new dae::PlotComponent(go);
	//go->AddComponent(plot);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}