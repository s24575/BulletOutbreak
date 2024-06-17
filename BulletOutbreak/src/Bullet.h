#pragma once

#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(glm::vec2 position, glm::vec2 size, glm::vec2 direction, float speed);

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) override;

private:
    glm::vec2 m_Direction;
    float m_Speed;
};
