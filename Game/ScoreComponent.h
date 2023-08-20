#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent final : public Component, public Subject
	{
	public:
		ScoreComponent(GameObject* parent);
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void ChangeScore(int amount);
		int GetScore() const { return m_Score; }
	private:
		int m_Score{};
	};
}
