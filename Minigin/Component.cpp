#include "Component.h"

dae::Component::Component(GameObject* pParent)
	: m_pParent{ pParent }
{
}

dae::Component::~Component()
= default;

void dae::Component::Render() const
{
}
