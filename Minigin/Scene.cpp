#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	std::erase(m_Objects, object);
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update(const float& deltaTime)
{
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(),
		[](const std::shared_ptr<GameObject>& obj) {
			return obj->IsDestroyed();
		}),
		m_Objects.end());
	for (const auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::RenderUI() const
{
	for (const auto& object : m_Objects)
	{
		object->RenderUI();
	}
}

