#pragma once

#include <SDL.h>
#include <glm/vec2.hpp>

class Tile {
public:
    Tile(SDL_Texture* texture, glm::vec2 position, int width, int height);

    void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const;

    glm::vec2 GetPosition() const;

private:
    SDL_Texture* m_Texture;
    glm::vec2 m_Position;
    int m_Width;
    int m_Height;
};
