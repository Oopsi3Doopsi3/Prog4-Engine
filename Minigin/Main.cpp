#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "TextureRenderComponent.h"
#include "FpsComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureRenderComponent>();
	go->GetComponent<dae::TextureRenderComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureRenderComponent>();
	go->GetComponent<dae::TextureRenderComponent>()->SetTexture("logo.tga");
	go->GetTransform().SetPosition(216, 180, 0);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	to->AddComponent<dae::TextureRenderComponent>();
	to->AddComponent<dae::TextComponent>("Oopsie", font);
	to->GetTransform().SetPosition(240, 20, 0);
	scene.Add(to);

	auto fps = std::make_shared<dae::GameObject>();
	fps->AddComponent<dae::TextureRenderComponent>();
	fps->AddComponent<dae::TextComponent>("Fps Counter", font);
	fps->AddComponent<dae::FpsComponent>();
	fps->GetTransform().SetPosition(5, 20, 0);
	scene.Add(fps);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}