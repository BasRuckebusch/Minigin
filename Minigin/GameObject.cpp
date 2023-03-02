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

void dae::GameObject::Update(const float& deltaTime)
{
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
