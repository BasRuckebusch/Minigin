#include "GameObject.h"

#include <iostream>

#include "Component.h"

dae::GameObject::~GameObject()
{
	for (const auto* pComponent : m_pComponents)
	{
		RemoveComponent(pComponent);
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
	for (auto* pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
