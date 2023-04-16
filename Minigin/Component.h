#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component();

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void Render() const;
		virtual void RenderUI() const;

	protected:
		explicit Component(GameObject* pParent) : m_pParent(pParent) {}
		GameObject* GetParent() const { return m_pParent; }
	private:
		GameObject* m_pParent;
	};
}
