#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>

#include "CameraComponent.h"
#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "MoveComponent.h"
#include "Scene.h"
#include "TextureComponent.h"

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

int LoadLevelFromBMP(std::string& filename, dae::Scene* scene, glm::vec2& worldPos)
{

    scene->RemoveAll();

    std::ifstream file(filename, std::ios_base::binary);
    if (!file.is_open()) {
        std::cout << "Failed to open the bitmap file." << std::endl;
        return 1;
    }

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

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
    uint8_t* pixelData = new uint8_t[rowSize * infoHeader.height];

    // Read the pixel data
    file.read(reinterpret_cast<char*>(pixelData), rowSize * infoHeader.height);

    // Check if the pixel data was read successfully
    if (!file.is_open()) {
        std::cout << "Failed to read the pixel data." << std::endl;
        delete[] pixelData;
        file.close();
        return 1;
    }

    //   // Open the output file for writing
    //   std::ofstream outputFile("output.txt");
    //   if (!outputFile.is_open()) {
    //       std::cout << "Failed to create the output file." << std::endl;
    //       delete[] pixelData;
    //       file.close();
    //       return;
    //   }

     // Print the color of each pixel
    for (int y = infoHeader.height - 1; y >= 0; --y) { // Loop in reverse order
        for (int x = 0; x < infoHeader.width; ++x) {
            uint8_t* pixel = pixelData + y * rowSize + x * bytesPerPixel;

            uint8_t blue = pixel[0];
            uint8_t green = pixel[1];
            uint8_t red = pixel[2];

            //std::cout << "Pixel at (" << x << ", " << y << "): "
            //    << "R = " << static_cast<int>(red) << ", "
            //    << "G = " << static_cast<int>(green) << ", "
            //    << "B = " << static_cast<int>(blue) << std::endl;

            if (red == 255 && green == 255 && blue == 255)
            {
            }
            else if (red == 0 && green == 0 && blue == 0)
            {
                // Black = Wall
                auto go = std::make_shared<dae::GameObject>();
                go->AddComponent<dae::TextureComponent>("wall.tga");
                go->SetPosition((worldPos.x + x * 16), (worldPos.y + (infoHeader.height - 1 - y) * 16));
                scene->Add(go);
            }
            else if (red == 0 && green == 255 && blue == 0)
            {
                // Green = Player
                const auto player = std::make_shared<dae::GameObject>();
                player->SetPosition((worldPos.x + x * 16), (worldPos.y + (infoHeader.height - 1 - y) * 16));
                player->AddComponent<dae::TextureComponent>("player.tga");
                player->AddComponent<dae::MoveComponent>();
                player->AddComponent<dae::CameraComponent>();
                scene->Add(player);

                dae::InputManager::GetInstance().BindCommand(SDLK_a, new dae::MoveLeftRight(player.get(), false));
                dae::InputManager::GetInstance().BindCommand(SDLK_d, new dae::MoveLeftRight(player.get(), true));
                dae::InputManager::GetInstance().BindCommand(SDLK_w, new dae::MoveUpDown(player.get(), false));
                dae::InputManager::GetInstance().BindCommand(SDLK_s, new dae::MoveUpDown(player.get(), true));
            }
            else if (red == 255 && green == 0 && blue == 0) {

            }
            else
            {
            }
        }
    }

    // Clean up
    delete[] pixelData;
    file.close();
    //outputFile.close();

    return 0;
}