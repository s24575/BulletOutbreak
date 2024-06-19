#include "Enemy.h"
#include <stdio.h>
#include <glm/geometric.hpp>
#include "EntityManager.h"

Enemy::Enemy(glm::vec2 position, glm::vec2 size, float movementSpeed, float healthPoints)
	: Entity(position, size), m_MovementSpeed(movementSpeed), m_HealthPoints(healthPoints) {}

Enemy::~Enemy() {
	if (m_Texture)
		SDL_DestroyTexture(m_Texture);
}

void Enemy::LoadTexture(SDL_Renderer* renderer, const std::string& path) {
	m_Texture = IMG_LoadTexture(renderer, path.c_str());
}

void Enemy::Update(float deltaTime) {
	auto player = EntityManager::Instance().FindEntityWithTag("player");
	if (player) {
		glm::vec2 enemyToPlayerVector = player->GetPosition() - this->GetPosition();
		float enemyToPlayerMagnitude = glm::length(enemyToPlayerVector);
		m_Velocity += enemyToPlayerVector / enemyToPlayerMagnitude * m_MovementSpeed;
	}

	m_Position += m_Velocity * deltaTime;
	m_Velocity = glm::vec2();
}

void Enemy::OnCollision(std::shared_ptr<Entity> other) {
	if (other->HasTag("bullet")) {
		this->TakeDamage(10);
	}
}

void Enemy::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
	int renderWidth = static_cast<int>(m_Size.x * zoom);
	int renderHeight = static_cast<int>(m_Size.y * zoom);
	SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
	SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}

void Enemy::TakeDamage(float damage)
{
	m_HealthPoints -= damage;
	if (m_HealthPoints <= 0.0f)
		MarkForRemoval();
}
