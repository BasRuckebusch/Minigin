#include <string>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (const auto* pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}
};

void dae::GameObject::Update()
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::Render() const
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
