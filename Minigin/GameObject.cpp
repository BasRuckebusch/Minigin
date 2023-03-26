#include <utility>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject()
{
	for (const auto* pComponent : m_pComponents)
	{
		delete pComponent;
		pComponent = nullptr;
	}
}
void dae::GameObject::Update(float deltaTime)
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

void dae::GameObject::RenderUI() const
{
	for (const auto* pComponent : m_pComponents)
	{
		pComponent->RenderUI();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	SetLocalPosition(glm::vec3(x,y,0));
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_pParent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
		}
	}
	m_PositionIsDirty = false;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (const auto child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition)
{
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
			SetPositionDirty();
		}
	}
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = std::move(parent);
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_pChildren.push_back(child); 
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
}
