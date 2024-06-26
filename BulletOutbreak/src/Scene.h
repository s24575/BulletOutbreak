#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <glm/vec2.hpp>
#include "Tile.h"
#include "Camera.h"

class Scene {
public:
    Scene(int screenWidth, int screenHeight);
    ~Scene();

    void InitBackground(SDL_Renderer* renderer, const std::string& grassTileTextureFile, const std::string& wallTileTextureFile, int tileSize);
    void Draw(SDL_Renderer* renderer, const Camera& camera);

private:
    int m_ScreenWidth;
    int m_ScreenHeight;
    std::vector<std::shared_ptr<Tile>> m_Tiles;
    SDL_Texture* m_GrassTileTexture = nullptr;
    SDL_Texture* m_WallTileTexture = nullptr;
};
