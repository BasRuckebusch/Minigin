#pragma once
#include "Singleton.h"
#include "Subject.h"

namespace dae
{
	class GameObject;

	class ScoreManager final : public dae::Singleton<ScoreManager>, public Subject
	{
	public:
		void ChangeScore(int amount);
	private:
		int m_Score{};
	};
}
