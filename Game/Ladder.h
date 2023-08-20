#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class Scene;
	class Ladder final
	{
	public:
		Ladder(Scene* scene, const glm::vec2& position, int type);
		Ladder(Scene* scene, const glm::vec2& position, int type, bool right);
		~Ladder() = default;

		Ladder(const Ladder& other) = delete;
		Ladder(Ladder&& other) = delete;
		Ladder& operator=(const Ladder& other) = delete;
		Ladder& operator=(Ladder&& other) = delete;
	};
}

