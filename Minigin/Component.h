#pragma once
#include <memory>
#include <utility>

#include "GameObject.h"

namespace dae
{
	class GameObject;

	class Component
	{
		std::shared_ptr<GameObject> m_pParent;
	public:
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(const float& deltaTime) = 0;
		virtual void Render() const;

		//	const GameObject* GetParent() const { return m_pParent; }
		//	void SetParent(GameObject* pParent) { m_pParent = pParent; }

	protected:
		explicit Component(std::shared_ptr<GameObject> pParent) : m_pParent(std::move(pParent)) { m_pParent->AddComponent(this); }
		std::shared_ptr<GameObject> GetParent() const { return m_pParent; }
	};
}
