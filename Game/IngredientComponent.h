#pragma 
#include "Component.h"

namespace dae
{
	class ScoreComponent;
	class Scene;

	class IngredientComponent final : public Component 
	{
	public:
		IngredientComponent(GameObject* parent, int type);
		~IngredientComponent() override = default;

		IngredientComponent(const IngredientComponent& other) = delete;
		IngredientComponent(IngredientComponent&& other) = delete;
		IngredientComponent& operator=(const IngredientComponent& other) = delete;
		IngredientComponent& operator=(IngredientComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void Fall();
		void StopFalling();
		void HitPart(int partHit);

		bool GetFalling() const { return m_IsFalling; }
		bool GetType() const { return m_Type; }

		void SetScoreComponent(ScoreComponent* score);

	private:
		static bool AllGreaterThan(const std::vector<int>& numbers, int num);

		int m_Type{};
		bool m_IsFalling{false};
		std::vector<int> m_PartsHit{ 0,0,0,0 };
		float m_XPos{};
		float m_YPos{};
		float m_FallSpeed{30};
		ScoreComponent* m_pScore{ nullptr };
	};
}