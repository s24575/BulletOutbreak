#include "Tile.h"
#include <cmath>

Tile::Tile(SDL_Texture* texture, glm::vec2 position, int width, int height)
    : m_Texture(texture), m_Position(position), m_Width(width), m_Height(height) {}

void Tile::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
    int renderWidth = std::round(m_Width * zoom);
    int renderHeight = std::round(m_Height * zoom);
    SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
    SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}

glm::vec2 Tile::GetPosition() const
{
    return m_Position;
}
