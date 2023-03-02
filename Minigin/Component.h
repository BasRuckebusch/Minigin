#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pParent);
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(const float& deltaTime) = 0;
		virtual void Render() const;

		const GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* pParent) { m_pParent = pParent; }

	protected:
		GameObject* m_pParent;
	};
}
