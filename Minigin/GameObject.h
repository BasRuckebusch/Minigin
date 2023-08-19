#pragma once
#include <algorithm>
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
		void Update(float deltaTime) const;
		void Render() const;
		void RenderUI() const;

		void Destroy() { m_IsDestroyed = true; }
		bool IsDestroyed() const { return m_IsDestroyed; }

		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& pos);
		//const Transform* GetTransform() const { return &m_Transform; }
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void SetPositionDirty();
		std::shared_ptr<GameObject> GetParent() const { return m_pParent; }

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename Component>
		Component* GetComponent() const;
		template <typename Component>
		std::vector<Component*> GetComponents();
		template <class Component, class ... Arguments>
		Component* AddComponent(Arguments&& ... args);
		template <class Component>
		void RemoveComponent();
		template <class Component>
		bool HasComponent() const;

		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPosition);

	private:
		//Transform m_Transform{};
		bool m_PositionIsDirty{ true };
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};
		std::vector<std::unique_ptr<Component>> m_pComponents;

		bool m_IsDestroyed{ false };

		std::shared_ptr<GameObject> m_pParent;
		std::vector<std::unique_ptr<GameObject>> m_pChildren;

		void UpdateWorldPosition();

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};

	template<typename Component>
	Component* GameObject::GetComponent() const
	{
		for (const auto& pComponent : m_pComponents)
		{
			if (Component* pComp = dynamic_cast<Component*>(pComponent.get()))
			{
				return pComp;
			}
		}
		return nullptr;
	}
	template<typename Component>
	std::vector<Component*> GameObject::GetComponents()
	{
		std::vector<Component*> pComps{};
		for (const auto& pComponent : m_pComponents)
		{
			if (Component* pComp = dynamic_cast<Component*>(pComponent.get()))
			{
				pComps.push_back(pComp);
			}
		}
		return pComps;
	}
	template<typename Component, typename...Arguments>
	Component* GameObject::AddComponent(Arguments&&... args)
	{
		std::unique_ptr<Component> pComponent = std::make_unique<Component>(this, std::forward<Arguments>(args)...);
		Component* rawPtr = pComponent.get();
		m_pComponents.push_back(std::move(pComponent));
		return rawPtr;
	}
	template<typename Component>
	void GameObject::RemoveComponent()
	{
		if (HasComponent<Component>())
		{
			auto it = std::remove_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& pComponent)
				{
					return dynamic_cast<Component*>(pComponent.get()) != nullptr;
				}
			);
			m_pComponents.erase(it, m_pComponents.end());
		}
	}
	template<typename Component>
	bool GameObject::HasComponent() const
	{
		return std::any_of(m_pComponents.begin(), m_pComponents.end(), [](const auto& pComponent)
			{
				return dynamic_cast<Component*>(pComponent.get()) != nullptr;
			}
		);
	}
}
