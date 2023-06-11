#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>

#include "BomberManComponent.h"
#include "CameraComponent.h"
#include "CollisionManager.h"
#include "CollisionComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "CustomCommand.h"
#include "EndComponent.h"
#include "EnemyComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "TextComponent.h"

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

inline int LoadLevelFromBMP(const std::string& filename, dae::Scene* scene, const glm::vec2& worldPos, int tileSize)
{

	std::srand(static_cast<unsigned>(std::time(nullptr)));

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

	auto& collisions = dae::CollisionManager::GetInstance();

	// Check the color of each pixel
	for (int y = infoHeader.height - 1; y >= 0; --y) { // Loop in reverse order
		for (int x = 0; x < infoHeader.width; ++x) {
			uint8_t* pixel = pixelData.get() + y * rowSize + x * bytesPerPixel;

			uint8_t blue = pixel[0];
			uint8_t green = pixel[1];
			uint8_t red = pixel[2];

			if (red == 255 && green == 255 && blue == 255)
			{
				//White = Nothing
			}
			else if (red == 0 && green == 0 && blue == 0)
			{
				// Black = Wall
				auto go = std::make_shared<dae::GameObject>();
				go->AddComponent<dae::TextureComponent>("wall.tga");
				go->SetPosition((worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize));
				go->AddComponent<dae::CollisionComponent>(go->GetWorldPosition(), tileSize, tileSize);
				scene->Add(go);

				collisions.AddWall(go);
			}
			else if (red == 0 && green == 255 && blue == 0)
			{
				// Green = Player
				const auto player = std::make_shared<dae::GameObject>();
				player->SetPosition((worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize));
				player->AddComponent<dae::TextureComponent>("player.tga");
				player->AddComponent<dae::MoveComponent>();
				const auto camera = player->AddComponent<dae::CameraComponent>();
				glm::vec2 offset{4,4};
				const auto colcomp = player->AddComponent<dae::CollisionComponent>(player->GetWorldPosition(), static_cast<int>(tileSize - offset.x * 2), static_cast<int>(tileSize - offset.y * 2));
				colcomp->SetOffset(offset);
				const auto bcomp = player->AddComponent<dae::BomberManComponent>(scene, tileSize);
				bcomp->SetLevelName("level.bmp");
				scene->Add(player);

				collisions.AddPlayer(player);

				auto& renderer = dae::Renderer::GetInstance();

				camera->SetBoundaries({ worldPos.x, infoHeader.width * tileSize / renderer.GetCameraScale() - tileSize * 5 / renderer.GetCameraScale() });


				dae::InputManager::GetInstance().BindCommand(SDLK_a, std::make_unique<dae::MoveLeftRight>(player.get(), false));
				dae::InputManager::GetInstance().BindCommand(SDLK_d, std::make_unique<dae::MoveLeftRight>(player.get(), true));
				dae::InputManager::GetInstance().BindCommand(SDLK_w, std::make_unique<dae::MoveUpDown>(player.get(), false));
				dae::InputManager::GetInstance().BindCommand(SDLK_s, std::make_unique<dae::MoveUpDown>(player.get(), true));
				dae::InputManager::GetInstance().BindCommand(SDLK_e, std::make_unique<dae::PlaceBomb>(player.get()));
			}
			else if (red == 255 && green == 0 && blue == 0) 
			{
				//Red = Enemy
				const auto enemy = std::make_shared<dae::GameObject>();
				enemy->SetPosition((worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize));
				enemy->AddComponent<dae::TextureComponent>("enemy.tga");
				enemy->AddComponent<dae::EnemyComponent>();
				enemy->AddComponent<dae::CollisionComponent>(enemy->GetWorldPosition(), tileSize, tileSize);
				scene->Add(enemy);
				collisions.AddEnemy(enemy);

			}
			else if (red == 0 && green == 0 && blue == 255) 
			{
				// Blue = Breakable Wall

				if (const int r = rand() % 11; r != 0)
				{
					auto go = std::make_shared<dae::GameObject>();
					go->AddComponent<dae::TextureComponent>("brick.tga");
					go->SetPosition((worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize));
					go->AddComponent<dae::CollisionComponent>(go->GetWorldPosition(), tileSize, tileSize);
					scene->Add(go);

					collisions.AddWall(go);
					collisions.AddBrick(go);
				}
			}
			else if (red == 255 && green == 255 && blue == 0)
			{
				// Yellow = End

				auto go = std::make_shared<dae::GameObject>();
				go->AddComponent<dae::TextureComponent>("end.tga");
				go->SetPosition((worldPos.x + x * tileSize), (worldPos.y + (infoHeader.height - 1 - y) * tileSize));
				go->AddComponent<dae::CollisionComponent>(go->GetWorldPosition(), tileSize, tileSize);
				std::vector<std::string> levelNames{ "level.bmp", "level5.bmp", "level2.bmp", "level3.bmp" };
				go->AddComponent<dae::EndComponent>(scene, levelNames);
				scene->Add(go);

			}
		}
	}

	// Clean up
	file.close();

	return 0;
}

inline void LoadLevel(const std::string& levelName, dae::Scene* scene)
{
	const auto objects = scene->GetAll();
	for (const auto& gameObject : objects)
	{
		gameObject->Destroy();
	}

	// Camera and background
	auto& renderer = dae::Renderer::GetInstance();
	renderer.SetBackgroundColor(SDL_Color(57, 132, 0));
	renderer.SetCameraPosition(glm::vec2(0, -32));
	renderer.SetCameraScale(2.f);
	
	auto& collisions = dae::CollisionManager::GetInstance();
	collisions.RemoveAll();
	
	// Load scene from file
	int tileSize{ 16 };
	
	std::string file{dae::ResourceManager::GetInstance().GetFullFilePath(levelName) };
	glm::vec2 worldPos = { 0, 0 };
	LoadLevelFromBMP(file, scene, worldPos, tileSize);


	// FPS counter
	auto go = std::make_shared<dae::GameObject>();
	const auto fpsfont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->AddComponent<dae::TextComponent>("0", fpsfont, SDL_Color(0, 255, 0));
	go->AddComponent<dae::FPSComponent>();
	go->SetPosition(0, -16);
	scene->Add(go);
}