#include "Scene.h"
#include <SDL_image.h>
#include "EntityManager.h"

Scene::Scene(int screenWidth, int screenHeight)
    : m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight) {}

Scene::~Scene() {
    if (m_GrassTileTexture)
        SDL_DestroyTexture(m_GrassTileTexture);
    if (m_WallTileTexture)
        SDL_DestroyTexture(m_WallTileTexture);
}

static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string& path) {
    return IMG_LoadTexture(renderer, path.c_str());
}

void Scene::InitBackground(SDL_Renderer* renderer, const std::string& grassTileTextureFile, const std::string& wallTileTextureFile, int tileSize) {
    m_GrassTileTexture = LoadTexture(renderer, grassTileTextureFile);
    m_WallTileTexture = LoadTexture(renderer, wallTileTextureFile);

    int numTilesX = 64;
    int numTilesY = 64;

    for (int y = 0; y < numTilesY; ++y) {
        for (int x = 0; x < numTilesX; ++x) {
            glm::vec2 position(x * tileSize - numTilesX * tileSize / 2, y * tileSize - numTilesY * tileSize / 2);

            if (x == 0 || x == numTilesX - 1 || y == 0 || y == numTilesY - 1) {
                std::shared_ptr<Tile> tile = std::make_unique<Tile>(m_WallTileTexture, position, glm::vec2((float)tileSize));
                tile->AddTag("collision");
                EntityManager::Instance().AddEntity(tile);
            }
            else {
                m_Tiles.emplace_back(std::make_unique<Tile>(m_GrassTileTexture, position, glm::vec2((float)tileSize)));
            }
        }
    }
}

void Scene::Draw(SDL_Renderer* renderer, const Camera& camera) {
    for (const auto& tile : m_Tiles) {
        glm::vec2 tileScreenPos = camera.WorldToScreen(tile->GetPosition());
        tile->Draw(renderer, tileScreenPos, camera.GetZoom());
    }
}
