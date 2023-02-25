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
		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y);
		const Transform* GetTransform() const { return &m_transform; }

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template<typename Component>
		Component* GetComponent() const;
		template<typename Component>
		Component* AddComponent(Component* pComponent);

	private:
		Transform m_transform{};
		std::vector<Component*> m_pComponents;

	};

	template<typename Component>
	Component* GameObject::GetComponent() const
	{
		return nullptr;
	}
	template<typename Component>
	Component* GameObject::AddComponent(Component* pComponent)
	{
		m_pComponents.push_back(pComponent);
		pComponent->SetParent(this);
		return pComponent;
	}
}
