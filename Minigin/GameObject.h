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
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		//const Transform* GetTransform() const { return &m_Transform; }
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetPositionDirty();
		const std::shared_ptr<GameObject> GetParent() const { return m_pParent; }

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

		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition);

	private:
		//Transform m_Transform{};
		bool m_PositionIsDirty{ true };
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};
		std::vector<Component*> m_pComponents;

		std::shared_ptr<GameObject> m_pParent;
		std::vector<GameObject*> m_pChildren;

		void UpdateWorldPosition();

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
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
			const Component* pComp = dynamic_cast<Component*>(pComponent);
			if (pComp)
			{
				return true;
			}
		}
		return false;
	}
}
