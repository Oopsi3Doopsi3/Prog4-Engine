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
#include "RotatorComponent.h"
#include "PlotComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	dae::GameObject* background = scene.Add("Background");
	auto textureRenderer1 = new dae::TextureRenderComponent(background);
	textureRenderer1->SetTexture("background.tga");
	background->AddComponent(textureRenderer1);

	dae::GameObject* logo = scene.Add("Logo");
	auto textureRenderer2 = new dae::TextureRenderComponent(logo);
	textureRenderer2->SetTexture("logo.tga");
	logo->AddComponent(textureRenderer2);
	logo->GetTransform().SetLocalPosition(216, 180, 0);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	dae::GameObject* parent = scene.Add("Parent");
	auto textureRenderer3 = new dae::TextureRenderComponent(parent);
	auto text1 = new dae::TextComponent(parent, "P", font);
	auto rotator1 = new dae::RotatorComponent(parent, glm::vec3{ 180,300,0 });
	parent->AddComponent(textureRenderer3);
	parent->AddComponent(text1);
	parent->GetTransform().SetLocalPosition(180, 300, 0);
	parent->AddComponent(rotator1);

	dae::GameObject* child = scene.Add("Child");
	auto textureRenderer4 = new dae::TextureRenderComponent(child);
	auto text2 = new dae::TextComponent(child, "C", font);
	auto rotator2 = new dae::RotatorComponent(child, parent->GetTransform().GetWorldPosition());
	child->AddComponent(textureRenderer4);
	child->AddComponent(text2);
	child->GetTransform().SetLocalPosition(50, 50, 0);
	child->AddComponent(rotator2);
	child->SetParent(parent, false);
	
	dae::GameObject* fps = scene.Add("Fps");
	auto textureRenderer5 = new dae::TextureRenderComponent(fps);
	auto text3 = new dae::TextComponent(fps, "Fps Counter", font);
	auto fpsComp = new dae::FpsComponent(fps);
	fps->AddComponent(textureRenderer5);
	fps->AddComponent(text3);
	fps->AddComponent(fpsComp);
	fps->GetTransform().SetLocalPosition(5, 20, 0);

	dae::GameObject* go = scene.Add("Graph");
	auto plot = new dae::PlotComponent(go);
	go->AddComponent(plot);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}