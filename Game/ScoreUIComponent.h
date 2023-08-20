#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class TextComponent;

	class ScoreUIComponent final : public Component, public Observer
	{
	public:
		ScoreUIComponent(GameObject* parent);
		~ScoreUIComponent() override = default;

		ScoreUIComponent(const ScoreUIComponent& other) = delete;
		ScoreUIComponent(ScoreUIComponent&& other) = delete;
		ScoreUIComponent& operator=(const ScoreUIComponent& other) = delete;
		ScoreUIComponent& operator=(ScoreUIComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void Notify(const GameObject* actor, Event events) override;

	private:
		TextComponent* m_pText{ nullptr };
	};
}
