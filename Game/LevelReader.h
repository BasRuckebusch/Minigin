#pragma once
#include <string>
#include <glm/vec2.hpp>

namespace dae
{
	class Scene;

	class LevelReader final
	{
	public:
		LevelReader(std::string& file, Scene* scene, glm::vec2& worldPos);

		LevelReader(const LevelReader& other) = delete;
		LevelReader(LevelReader&& other) = delete;
		LevelReader& operator=(const LevelReader& other) = delete;
		LevelReader& operator=(LevelReader&& other) = delete;
	private:
	};
}


