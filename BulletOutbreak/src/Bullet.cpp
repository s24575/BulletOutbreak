#include "Bullet.h"
#include <glm/geometric.hpp>

Bullet::Bullet(glm::vec2 position, glm::vec2 size, glm::vec2 direction, float speed)
    : Entity(position, size), m_Direction(glm::normalize(direction)), m_Speed(speed) {}

void Bullet::Update(float deltaTime) {
    m_Position += m_Direction * m_Speed * deltaTime;
}

void Bullet::HandleCollision(std::shared_ptr<Entity> other)
{
}

void Bullet::OnCollision(std::shared_ptr<Entity> other) {
    if (other->HasTag("enemy")) {
        this->MarkForRemoval();
    }
}

void Bullet::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
    int renderWidth = static_cast<int>(m_Size.x * zoom);
    int renderHeight = static_cast<int>(m_Size.y * zoom);
    SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &renderQuad);
}
