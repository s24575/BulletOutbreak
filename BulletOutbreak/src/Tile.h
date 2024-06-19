#pragma once

#include <SDL.h>
#include <glm/vec2.hpp>
#include "Entity.h"

class Tile : public Entity {
public:
    Tile(SDL_Texture* texture, glm::vec2 position, glm::vec2 size);

    void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const;

private:
    SDL_Texture* m_Texture;
};
