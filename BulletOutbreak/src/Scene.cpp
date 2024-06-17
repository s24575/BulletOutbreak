#include "Scene.h"
#include <SDL_image.h>

Scene::Scene(int screenWidth, int screenHeight)
    : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight) {}

Scene::~Scene() {
    if (m_TileTexture)
        SDL_DestroyTexture(m_TileTexture);
}

static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path) {
    return IMG_LoadTexture(renderer, path.c_str());
}

void Scene::InitBackground(SDL_Renderer* renderer, const std::string& tileTextureFile, int tileSize) {
    m_TileTexture = LoadTexture(renderer, tileTextureFile);

    int numTilesX = 128;
    int numTilesY = 128;

    for (int y = 0; y < numTilesY; ++y) {
        for (int x = 0; x < numTilesX; ++x) {
            glm::vec2 position(x * tileSize - numTilesX * tileSize / 2, y * tileSize - numTilesY * tileSize / 2);
            m_Tiles.emplace_back(std::make_unique<Tile>(m_TileTexture, position, tileSize, tileSize));
        }
    }
}

void Scene::Draw(SDL_Renderer* renderer, const Camera& camera) {
    for (const auto& tile : m_Tiles) {
        glm::vec2 tileScreenPos = camera.WorldToScreen(tile->GetPosition());
        tile->Draw(renderer, tileScreenPos, camera.GetZoom());
    }
}
