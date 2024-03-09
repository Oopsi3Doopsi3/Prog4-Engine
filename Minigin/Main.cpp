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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<dae::GameObject>();
	//auto textureRenderer1 = new dae::TextureRenderComponent(go.get());
	//textureRenderer1->SetTexture("background.tga");
	//go->AddComponent(textureRenderer1);
	//scene.Add(go);

	//go = std::make_shared<dae::GameObject>();
	//auto textureRenderer2 = new dae::TextureRenderComponent(go.get());
	//textureRenderer2->SetTexture("logo.tga");
	//go->AddComponent(textureRenderer2);
	//go->GetTransform().SetLocalPosition(216, 180, 0);
	//scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto parent = std::make_shared<dae::GameObject>();
	auto textureRenderer3 = new dae::TextureRenderComponent(parent.get());
	auto text1 = new dae::TextComponent(parent.get(), "P", font);
	auto rotator1 = new dae::RotatorComponent(parent.get(), glm::vec3{ 180,300,0 });
	parent->AddComponent(textureRenderer3);
	parent->AddComponent(text1);
	parent->GetTransform().SetLocalPosition(180, 300, 0);
	parent->AddComponent(rotator1);
	scene.Add(parent);

	//auto child = std::make_shared<dae::GameObject>();
	//auto textureRenderer4 = new dae::TextureRenderComponent(child.get());
	//auto text2 = new dae::TextComponent(child.get(), "C", font);
	//auto rotator2 = new dae::RotatorComponent(child.get(), parent->GetTransform().GetWorldPosition());
	//child->AddComponent(textureRenderer4);
	//child->AddComponent(text2);
	//child->GetTransform().SetLocalPosition(50, 50, 0);
	//child->AddComponent(rotator2);
	//child->SetParent(parent, false);
	//scene.Add(child);
	//
	//auto fps = std::make_shared<dae::GameObject>();
	//auto textureRenderer5 = new dae::TextureRenderComponent(fps.get());
	//auto text3 = new dae::TextComponent(fps.get(), "Fps Counter", font);
	//auto fpsComp = new dae::FpsComponent(fps.get());
	//fps->AddComponent(textureRenderer5);
	//fps->AddComponent(text3);
	//fps->AddComponent(fpsComp);
	//fps->GetTransform().SetLocalPosition(5, 20, 0);
	//scene.Add(fps);

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}