#include "Tile.h"
#include <cmath>

Tile::Tile(SDL_Texture* texture, glm::vec2 position, glm::vec2 size)
    : Entity(position, size), m_Texture(texture) {}

void Tile::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
    int renderWidth = std::ceil(m_Size.x * zoom);
    int renderHeight = std::ceil(m_Size.y * zoom);
    SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
    SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}
