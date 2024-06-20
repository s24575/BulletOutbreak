#include "Player.h"
#include <stdio.h>
#include <glm/geometric.hpp>
#include "EntityManager.h"
#include <iostream>

Player::Player(glm::vec2 position, glm::vec2 size, float movementSpeed)
	: Entity(position, size), m_MovementSpeed(movementSpeed) {}

Player::~Player() {
	if (m_Texture)
		SDL_DestroyTexture(m_Texture);
}

void Player::LoadTexture(SDL_Renderer* renderer, const std::string& path) {
	m_Texture = IMG_LoadTexture(renderer, path.c_str());
}

void Player::HandleInput(const glm::vec2& moveDirection)
{
	if (glm::length(moveDirection) != 0) {
		m_MoveForce = glm::normalize(moveDirection) * m_MovementSpeed;
	}
	else
	{
		m_MoveForce = glm::vec2();
	}
}

void Player::Update(float deltaTime) {
	if (!IsAlive()) {
		RemoveTag("collision");
		return;
	}

	auto enemies = EntityManager::Instance().FindEntitiesWithTag("enemy");
	for (const auto& enemy : enemies) {
		auto enemyToPlayerVector = this->GetPosition() - enemy->GetPosition();
		if (glm::length(enemyToPlayerVector) < 2.5f) {
			m_ForceToApply += glm::normalize(enemyToPlayerVector) * 10.0f;
			TakeDamage(10.0f);
		}
	}

	m_MoveForce += m_ForceToApply;

	if (glm::length(m_ForceToApply) < 0.01f)
		m_ForceToApply = glm::vec2(0.0f);
	else
		m_ForceToApply /= 1.0f + 1.0f * deltaTime;


	m_Velocity = m_MoveForce;
	m_Position += m_Velocity * deltaTime + 0.5f * m_Acceleration * deltaTime * deltaTime;
}

void Player::TakeDamage(float damage) {
	m_HealthPoints -= damage;
}

bool Player::IsAlive() const
{
	return m_HealthPoints > 0.0f;
}

void Player::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
	int renderWidth = static_cast<int>(m_Size.x * zoom);
	int renderHeight = static_cast<int>(m_Size.y * zoom);
	SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
	SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}
