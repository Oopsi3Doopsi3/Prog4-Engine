#include "Scene.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

GameObject* Scene::Add(const std::string& name)
{
	m_objects.emplace_back(std::make_unique<GameObject>(name));
	return m_objects.back().get();
}

void Scene::Remove()
{
	//m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::LateUpdate()
{
	for(auto& object : m_objects)
	{
		object->LateUpdate();
	}

	for(auto& object : m_objects)
	{
		object->DestroyComponents();
	}

	DestroyObjects();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::DestroyObjects()
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[](const std::unique_ptr<GameObject>& go) {return go->GetMarkedDestroy(); }
		),
		m_objects.end()
	);
}