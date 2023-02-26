#pragma once
#include <memory>
#include <vector>

#include "Transform.h"

namespace dae
{
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		void Update(const float& deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		const Transform* GetTransform() const { return &m_Transform; }

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template<typename Component>
		Component* GetComponent() const;
		template<typename Component>
		Component* AddComponent(Component* pComponent);
		template<typename Component>
		void RemoveComponent(Component* pComponent);
		template<typename Component>
		bool HasComponent(Component* pComponent) const;


	private:
		Transform m_Transform{};
		std::vector<Component*> m_pComponents;

	};

	template<typename Component>
	Component* GameObject::GetComponent() const
	{
		for (auto* pComponent : m_pComponents)
		{
			if (Component* pComp = dynamic_cast<Component*>(pComponent))
			{
				return pComp;
			}
		}
		return nullptr;
	}
	template<typename Component>
	Component* GameObject::AddComponent(Component* pComponent)
	{
		m_pComponents.push_back(pComponent);
		pComponent->SetParent(this);
		return pComponent;
	}
	template<typename Component>
	void GameObject::RemoveComponent(Component* pComponent)
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent), m_pComponents.end());
		delete pComponent;
	}
	template<typename Component>
	bool GameObject::HasComponent(Component* pComponent) const
	{
		for (const auto* pComponent : m_pComponents)
		{
			Component* pComp = dynamic_cast<Component*>(pComponent);
			if (pComp)
			{
				return true;
			}
		}
		return false;
	}
}
