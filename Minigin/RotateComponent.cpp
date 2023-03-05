#include "RotateComponent.h"
#include <cmath>

dae::RotateComponent::RotateComponent(float radius) :
	Component(nullptr),
	m_Radius(radius)
{
	
}

void dae::RotateComponent::Update([[maybe_unused]] const float& deltaTime)
{
	m_Angle += deltaTime;

	float x = m_Radius * cos(m_Angle);
	float y = m_Radius * sin(m_Angle);

	//if (m_pParent->GetParent() != nullptr)
	//{
	//	x += m_pParent->GetParent()->GetLocalPosition().x - m_pParent->GetLocalPosition().x;
	//	y += m_pParent->GetParent()->GetLocalPosition().y - m_pParent->GetLocalPosition().y;
	//}
	//else
	//{
	//	x += m_pParent->GetLocalPosition().x;
	//	y += m_pParent->GetLocalPosition().y;
	//}

	x += m_pParent->GetLocalPosition().x;
	y += m_pParent->GetLocalPosition().y;

	m_pParent->SetLocalPosition(glm::vec3(x,y,0));
}

void dae::RotateComponent::Render() const
{
}

//	glm::vec3 dae::RotateComponent::RotatePoint(glm::vec3 point, glm::vec3 center, double angle) const
//	{
//		float c = cos(angle);
//		float s = sin(angle);
//		float rx{};
//		float ry{};
//		rx = (point.x - center.x) * s + (point.y - center.y) * c + center.y;
//		ry = (point.x - center.x) * c - (point.y - center.y) * s + point.x;
//	
//		return {rx, ry, 0};
//	}
