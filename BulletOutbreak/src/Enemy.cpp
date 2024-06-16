#include "Enemy.h"
#include <stdio.h>
#include <glm/geometric.hpp>

Enemy::Enemy()
	: m_Texture(nullptr), m_Position(glm::vec2()), m_Velocity(glm::vec2()), m_MovementSpeed(200), m_Width(50), m_Height(50) {}

Enemy::~Enemy() {
	SDL_DestroyTexture(m_Texture);
}

void Enemy::LoadTexture(SDL_Renderer* renderer, const std::string& path) {
	m_Texture = IMG_LoadTexture(renderer, path.c_str());
}

void Enemy::Update(float deltaTime) {
	m_Position += m_Velocity * deltaTime;
	m_Velocity = glm::vec2();
}

void Enemy::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
	int renderWidth = static_cast<int>(m_Width * zoom);
	int renderHeight = static_cast<int>(m_Height * zoom);
	SDL_Rect renderQuad = { static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), renderWidth, renderHeight };
	SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}