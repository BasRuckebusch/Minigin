#include "IngredientComponent.h"

#include "BoxColliderComponent.h"
#include "CollisionManager.h"
#include "ScoreComponent.h"
#include "TextureComponent.h"

dae::IngredientComponent::IngredientComponent(GameObject* parent, int type) :
	Component(parent),
	m_Type(type)
{
	auto& pos = GetParent()->GetLocalPosition();
	m_XPos = pos.x;
	m_YPos = pos.y;
}

void dae::IngredientComponent::Update(float deltaTime)
{
	if (m_IsFalling)
	{
		m_YPos += m_FallSpeed * deltaTime;
		GetParent()->SetLocalPosition({ m_XPos, m_YPos, 0 });

		const std::vector<BoxColliderComponent*> colliders = GetParent()->GetComponents<BoxColliderComponent>();
		if (!colliders.empty())
		{
			for (const auto collider : colliders)
			{
				collider->SetPosition({ m_XPos, m_YPos });
			}
		}
		const auto& collisions = CollisionManager::GetInstance();
		collisions.ChainFall(GetParent(), GetParent()->GetComponent<BoxColliderComponent>()->GetRect());
	}
}

void dae::IngredientComponent::Render() const
{
}

void dae::IngredientComponent::Fall()
{
	m_IsFalling =true;
	for (const auto& texture : GetParent()->GetComponents<TextureComponent>())
	{
		glm::vec2 offset = texture->GetOffset();
		texture->SetOffset({ offset.x, 0 });
	}
	m_YPos += 3;
	GetParent()->SetLocalPosition({ m_XPos, m_YPos, 0 });

	const std::vector<BoxColliderComponent*> colliders = GetParent()->GetComponents<BoxColliderComponent>();
	if (!colliders.empty())
	{
		for (const auto collider : colliders)
		{
			collider->SetPosition({ m_XPos, m_YPos });
		}
	}
}

void dae::IngredientComponent::StopFalling()
{
	m_IsFalling = false;
	for (auto& i : m_PartsHit)
	{
		i = 0;
	}
	if (m_pScore)
		m_pScore->ChangeScore(50);
	if (m_Type == 0)
	{
		auto& collisions = CollisionManager::GetInstance();
		collisions.InPot(GetParent(), GetParent()->GetComponent<BoxColliderComponent>()->GetRect());
	}
}

void dae::IngredientComponent::HitPart(int partHit)
{
	if (m_PartsHit[partHit] == 0)
	{
		m_PartsHit[partHit]++;
		auto tex = GetParent()->GetComponents<TextureComponent>().at(partHit);
		glm::vec2 offset = tex->GetOffset();
		tex->SetOffset({ offset.x, offset.y +1 });
	}
	if (AllGreaterThan(m_PartsHit, 0))
		Fall();
}

void dae::IngredientComponent::SetScoreComponent(ScoreComponent* score)
{
	m_pScore = score;
}

bool dae::IngredientComponent::AllGreaterThan(const std::vector<int>& numbers, int n)
{
	for (const int num : numbers)
	{
		if (num <= n) 
			return false;
	}
	return true; 
}

