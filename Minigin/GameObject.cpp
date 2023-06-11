#include <utility>
#include "GameObject.h"
#include "Component.h"
#include "ResourceManager.h"

dae::GameObject::~GameObject()
{
	m_pComponents.clear();
	m_pChildren.clear();
}
void dae::GameObject::Update(float deltaTime) const
{
	if (!m_pComponents.empty())
	{
		for (const auto& pComponent : m_pComponents)
		{
			if (pComponent)
			{
				pComponent->Update(deltaTime);
			}

		}
		for (const auto& child : m_pChildren)
		{
			child->Update(deltaTime);
		}
	}
}

void dae::GameObject::Render() const
{
	for (const auto& pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::RenderUI() const
{
	for (const auto& pComponent : m_pComponents)
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
	for (const auto& child : m_pChildren)
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
	m_pChildren.push_back(std::unique_ptr<GameObject>(child));
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	std::erase_if(m_pChildren, [child](const auto& pChild) 
		{
			return pChild.get() == child;
		}
	);
}