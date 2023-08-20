#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>

#include "CollisionManager.h"
#include "GameObject.h"
#include "IngredientComponent.h"
#include "InputManager.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "CustomCommand.h"
#include "PeterComponent.h"
#include "ScoreComponent.h"
#include "ScoreUIComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"


//https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file

#pragma pack(push, 1) // Disable struct padding, data is stored in a packed format without this it won't work

// Bitmap file header structure
struct BitmapFileHeader
{
	uint16_t signature;
	uint32_t fileSize;
	uint32_t reserved;
	uint32_t dataOffset;
};

// Bitmap info header structure
struct BitmapInfoHeader
{
	uint32_t headerSize;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bitsPerPixel;
	uint32_t compression;
	uint32_t imageSize;
	int32_t xPixelsPerMeter;
	int32_t yPixelsPerMeter;
	uint32_t colorsUsed;
	uint32_t colorsImportant;
};
#pragma pack(pop) // Restore default struct padding

//Level Objects

inline void AddLadder(dae::Scene* scene, const glm::vec2& position, int type)
{
	const auto go = std::make_shared<dae::GameObject>();
	go->SetPosition(position);
	if (type == 0)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/LadderTop.tga");
	}
	else if (type == 1)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/Ladder.tga");
		const auto col = go->AddComponent<dae::BoxColliderComponent>(position, 10, 16);
		col->SetOffset({ 3, 0 });
	}
	else if (type == 2)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/LadderBottom.tga");

		const auto col = go->AddComponent<dae::BoxColliderComponent>(position, 10, 13);
		col->SetOffset({ 3, 0 });
	}
	if (type != 1)
	{
		go->AddComponent<dae::BoxColliderComponent>(position, 16, 2);
	}

	scene->Add(go);
	dae::CollisionManager::GetInstance().AddLadder(go);
}

inline void AddLadder(dae::Scene* scene, const glm::vec2& position, int type, bool right)
{
	const auto go = std::make_shared<dae::GameObject>();
	if (right)
	{
		switch (type)
		{
		case 0:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderRightTop.tga");
			break;
		case 1:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderRight.tga");
			break;
		case 2:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderRightBottom.tga");
			break;
		default:
			;
		}
	}
	else
	{
		switch (type)
		{
		case 0:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderLeftTop.tga");
			break;
		case 1:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderLeft.tga");
			break;
		case 2:
			go->AddComponent<dae::TextureComponent>("LevelObjects/LadderLeftBottom.tga");
			break;
		default:
			;
		}
		if (type != 0)
		{
			if (type == 2)
			{
				const auto col = go->AddComponent<dae::BoxColliderComponent>(position, 10, 13);
				col->SetOffset({ 11,0 });
			}
			else
			{
				const auto col = go->AddComponent<dae::BoxColliderComponent>(position, 10, 16);
				col->SetOffset({ 11,0 });
			}
		}
	}
	if (type != 1)
	{
		go->AddComponent<dae::BoxColliderComponent>(position, 16, 2);

		const auto stopper = std::make_shared<dae::GameObject>();
		const auto col = stopper->AddComponent<dae::BoxColliderComponent>(position, 8, 8);
		col->SetOffset({ 0, 8 });
		stopper->SetPosition(position);
		scene->Add(stopper);
		dae::CollisionManager::GetInstance().AddStopper(stopper);
	}

	go->SetPosition(position);
	scene->Add(go);

	dae::CollisionManager::GetInstance().AddLadder(go);
}

inline void AddPot(dae::Scene* scene, const glm::vec2& position, int type)
{
	const auto go = std::make_shared<dae::GameObject>();
	go->SetPosition(position);
	if (type == 0)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/PotLeft.tga");
	}
	else if (type == 1)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/PotMiddle.tga");

		const auto pot = std::make_shared<dae::GameObject>();
		pot->SetPosition(position);
		const auto col = pot->AddComponent<dae::BoxColliderComponent>(position, 8, 8);
		col->SetOffset({ 0, 8 });

		dae::CollisionManager::GetInstance().AddPot(pot);
	}
	else if (type == 2)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/PotDouble.tga");
	}
	else if (type == 3)
	{
		go->AddComponent<dae::TextureComponent>("LevelObjects/PotRight.tga");
	}

	scene->Add(go);
}

inline int LoadLevelFromBMP(const std::string& filename, dae::Scene* scene, const glm::vec2& worldPos, int tileSize)
{
	std::ifstream file(filename, std::ios_base::binary);
	if (!file) {
		std::cout << "Failed to open the bitmap file." << std::endl;
		return 1;
	}

	BitmapFileHeader fileHeader{};
	BitmapInfoHeader infoHeader{};

	// Read the file header
	file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

	// Read the info header
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

	// Check if the file is a valid bitmap
	if (fileHeader.signature != 0x4D42) {
		std::cout << "The file is not a valid bitmap." << std::endl;
		file.close();
		return 1;
	}

	// Calculate the number of bytes per pixel
	int bytesPerPixel = infoHeader.bitsPerPixel / 8;

	// Calculate the row size in bytes (including padding)
	int rowSize = ((infoHeader.width * bytesPerPixel + 3) & (~3));

	// Allocate memory for the pixel data
	const std::unique_ptr<uint8_t[]> pixelData(new uint8_t[rowSize * infoHeader.height]);

	// Read the pixel data
	file.read(reinterpret_cast<char*>(pixelData.get()), static_cast<std::streamsize>(rowSize) * infoHeader.height);


	// Check if the pixel data was read successfully
	if (!file) {
		std::cout << "Failed to read the pixel data." << std::endl;
		file.close();
		return 1;
	}

	uint8_t prevBlue{};

	// Check the color of each pixel
	for (int y = infoHeader.height - 1; y >= 0; --y) { // Loop in reverse order
		for (int x = 0; x < infoHeader.width; ++x) {
			uint8_t* pixel = pixelData.get() + y * rowSize + x * bytesPerPixel;

			uint8_t blue = pixel[0];
			uint8_t green = pixel[1];
			uint8_t red = pixel[2];

			glm::vec2 pos{ (worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize) };

			//Ladders
			if (red == 255)
			{
				if (blue == 0)
					AddLadder(scene, pos, 0);
				if (blue == 85)
					AddLadder(scene, pos, 1);
				if (blue == 170)
					AddLadder(scene, pos, 2);
			}
			// Double Ladders
			bool right{};
			if (prevBlue == 255)
				right = true;
			if (blue == 255)
			{
				if (red == 0)
					AddLadder(scene, pos, 0, right);
				if (red == 85)
					AddLadder(scene, pos, 1, right);
				if (red == 170)
					AddLadder(scene, pos, 2, right);
			}

			// Plates
			if (blue == 0 && red == 0)
			{
				if (green == 128)
					AddPot(scene, pos, 0);
				if (green == 255)
					AddPot(scene, pos, 1);
				if (green == 187)
					AddPot(scene, pos, 2);
				if (green == 64)
					AddPot(scene, pos, 3);
			}
			prevBlue = blue;
		}
	}

	// Clean up
	file.close();

	return 0;
}

//Ingredience
inline void AddIngredient(dae::Scene* scene, const glm::vec2& position, int type, int tileSize, std::shared_ptr<dae::GameObject > scoreGo)
{
	const auto go = std::make_shared<dae::GameObject>();
	go->SetPosition(position);
	for (int i = 1; i <= 4; ++i)
	{
		std::string texturePath = "Ingredients/ingredient" + std::to_string(i + (type * 4)) + ".tga";
		const auto tex = go->AddComponent<dae::TextureComponent>(texturePath.c_str());
		tex->SetOffset({ tileSize * (i - 1), 0 });
		const auto col = go->AddComponent<dae::BoxColliderComponent>(position, tileSize, tileSize);
		col->SetOffset({ tileSize * (i - 1), 0 });
	}
	const auto ingredient = go->AddComponent<dae::IngredientComponent>();
	ingredient->SetScoreComponent(scoreGo->GetComponent<dae::ScoreComponent>());
	scene->Add(go);
	
	// ^- ScoreComponent 

	dae::CollisionManager::GetInstance().AddIngredient(go);
}

inline int LoadIngredientsFromBMP(const std::string& filename, dae::Scene* scene, const glm::vec2& worldPos, int tileSize, std::shared_ptr<dae::GameObject > scoreGo)
{
	std::ifstream file(filename, std::ios_base::binary);
	if (!file) {
		std::cout << "Failed to open the bitmap file." << std::endl;
		return 1;
	}

	BitmapFileHeader fileHeader{};
	BitmapInfoHeader infoHeader{};

	// Read the file header
	file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

	// Read the info header
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

	// Check if the file is a valid bitmap
	if (fileHeader.signature != 0x4D42) {
		std::cout << "The file is not a valid bitmap." << std::endl;
		file.close();
		return 1;
	}

	// Calculate the number of bytes per pixel
	int bytesPerPixel = infoHeader.bitsPerPixel / 8;

	// Calculate the row size in bytes (including padding)
	int rowSize = ((infoHeader.width * bytesPerPixel + 3) & (~3));

	// Allocate memory for the pixel data
	const std::unique_ptr<uint8_t[]> pixelData(new uint8_t[rowSize * infoHeader.height]);

	// Read the pixel data
	file.read(reinterpret_cast<char*>(pixelData.get()), static_cast<std::streamsize>(rowSize) * infoHeader.height);


	// Check if the pixel data was read successfully
	if (!file) {
		std::cout << "Failed to read the pixel data." << std::endl;
		file.close();
		return 1;
	}


	// Check the color of each pixel
	for (int y = infoHeader.height - 1; y >= 0; --y) { // Loop in reverse order
		for (int x = 0; x < infoHeader.width; ++x) {
			uint8_t* pixel = pixelData.get() + y * rowSize + x * bytesPerPixel;

			uint8_t blue = pixel[0];
			uint8_t green = pixel[1];
			uint8_t red = pixel[2];

			glm::vec2 pos{ (worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize) };

			//Bun Bottom
			if (red == 255 && blue == 0 && green == 255)
				AddIngredient(scene, pos, 1, tileSize, scoreGo);
			//Lettuce
			if (red == 0 && blue == 0 && green == 255)
				AddIngredient(scene, pos, 5, tileSize, scoreGo);
			//Cheese
			if (red == 0 && blue == 255 && green == 255)
				AddIngredient(scene, pos, 2, tileSize, scoreGo);
			//Burger
			if (red == 255 && blue == 0 && green == 0)
				AddIngredient(scene, pos, 3, tileSize, scoreGo);
			//Tomato
			if (red == 0 && blue == 255 && green == 0)
				AddIngredient(scene, pos, 4, tileSize, scoreGo);
			//Bun Top
			if (red == 255 && blue == 255 && green == 0)
				AddIngredient(scene, pos, 0, tileSize, scoreGo);
		}
	}

	// Clean up
	file.close();

	return 0;
}

inline void SaveHighScore(dae::Scene* scene)
{
	const auto objects = scene->GetAll();
	for (const auto& gameObject : objects)
	{
		if (gameObject->HasComponent<dae::ScoreComponent>())
		{
			std::vector<int> highScores;
			int highScore = gameObject->GetComponent<dae::ScoreComponent>()->GetScore();
			highScores.push_back(highScore);

			// Read existing highscores
			std::string filePath = "high_scores.txt";
			std::ifstream inFile(filePath);
			int score{};
			while (inFile >> score)
			{
				highScores.push_back(score);
			}
			inFile.close();

			std::ranges::sort(highScores, std::greater<int>());

			std::ofstream outFile(filePath);

			if (outFile.is_open())
			{
				for (int i : highScores)
				{
					outFile << i << "\n";
				}
				outFile.close();
			}
			else
			{
				std::cerr << "Failed to open file." << std::endl;
			}
		}
	}
}

inline void LoadLevel(const std::string& levelName, dae::Scene* scene)
{
	const auto objects = scene->GetAll();
	SaveHighScore(scene);
	for (const auto& gameObject : objects)
	{
		gameObject->Destroy();
	}

	auto& collisions = dae::CollisionManager::GetInstance();
	collisions.RemoveAll();

	const auto font = dae::ResourceManager::GetInstance().LoadFont("hobo.otf", 12);

	const auto scoreGO = std::make_shared<dae::GameObject>();
	const auto score = scoreGO->AddComponent<dae::ScoreComponent>();
	scene->Add(scoreGO);

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>("Points: 0", font, SDL_Color(255, 255, 255));
	const auto ui = go->AddComponent<dae::ScoreUIComponent>();
	go->SetPosition(0, 4);
	scene->Add(go);

	score->AddObserver(ui);

	// Load scene from file
	int tileSize{ 16 };
	int halfTileSize{ tileSize /2 };

	std::string level = "LevelMaps/" + levelName;
	std::string ingredient = "IngredientMaps/" + levelName;
	glm::vec2 worldPos = { tileSize, tileSize };

	std::string levelfile{ dae::ResourceManager::GetInstance().GetFullFilePath(level) };
	std::string ingredientfile{ dae::ResourceManager::GetInstance().GetFullFilePath(ingredient) };
	
	LoadLevelFromBMP(levelfile, scene, worldPos, tileSize);
	LoadIngredientsFromBMP(ingredientfile, scene, worldPos, halfTileSize, scoreGO);

	const auto player = std::make_shared<dae::GameObject>();
	player->SetLocalPosition(glm::vec3(104, 62, 0));
	player->AddComponent<dae::TextureComponent>("player.tga");
	player->AddComponent<dae::MoveComponent>();
	player->AddComponent<dae::PeterComponent>();
	scene->Add(player);

	auto& input = dae::InputManager::GetInstance();

	input.BindCommand(dae::ControllerButton::Left, std::make_unique<dae::Move>(player.get(), glm::vec2{ -1.f, 0.f }), dae::EventState::keyPressed);
	input.BindCommand(dae::ControllerButton::Right, std::make_unique<dae::Move>(player.get(), glm::vec2{ 1.f, 0.f }), dae::EventState::keyPressed);
	input.BindCommand(dae::ControllerButton::Up, std::make_unique<dae::Move>(player.get(), glm::vec2{ 0.f, -1.f }), dae::EventState::keyPressed);
	input.BindCommand(dae::ControllerButton::Down, std::make_unique<dae::Move>(player.get(), glm::vec2{ 0.f, 1.f }), dae::EventState::keyPressed);

	input.BindCommand(SDLK_a, std::make_unique<dae::Move>(player.get(), glm::vec2{ -1.f, 0.f }), dae::EventState::keyPressed);
	input.BindCommand(SDLK_d, std::make_unique<dae::Move>(player.get(), glm::vec2{ 1.f, 0.f }), dae::EventState::keyPressed);
	input.BindCommand(SDLK_w, std::make_unique<dae::Move>(player.get(), glm::vec2{ 0.f, -1.f }), dae::EventState::keyPressed);
	input.BindCommand(SDLK_s, std::make_unique<dae::Move>(player.get(), glm::vec2{ 0.f, 1.f }), dae::EventState::keyPressed);
}

//inline void LoadLevel(const std::string& levelName, dae::Scene* scene)
//{
//	const auto objects = scene->GetAll();
//	for (const auto& gameObject : objects)
//	{
//		gameObject->Destroy();
//	}
//
//	// Camera and background
//	auto& renderer = dae::Renderer::GetInstance();
//	renderer.SetBackgroundColor(SDL_Color(57, 132, 0));
//	renderer.SetCameraPosition(glm::vec2(0, -32));
//	renderer.SetCameraScale(2.f);
//	
//	auto& collisions = dae::CollisionManager::GetInstance();
//	collisions.RemoveAll();
//	
//	// Load scene from file
//	int tileSize{ 16 };
//	
//	std::string file{dae::ResourceManager::GetInstance().GetFullFilePath(levelName) };
//	glm::vec2 worldPos = { 0, 0 };
//	LoadLevelFromBMP(file, scene, worldPos, tileSize);
//
//
//	// FPS counter
//	auto go = std::make_shared<dae::GameObject>();
//	const auto fpsfont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
//	go = std::make_shared<dae::GameObject>();
//	go->AddComponent<dae::TextureComponent>();
//	go->AddComponent<dae::TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
//	go->AddComponent<dae::FPSComponent>();
//	go->SetPosition(0, -16);
//	scene->Add(go);
//}