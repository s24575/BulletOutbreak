#include "Player.h"
#include <stdio.h>
#include <glm/geometric.hpp>

Player::Player()
	: m_Texture(nullptr), m_Position(glm::vec2()), m_Velocity(glm::vec2()), m_MovementSpeed(200), m_Width(50), m_Height(50) {}

Player::~Player() {
	SDL_DestroyTexture(m_Texture);
}

bool Player::LoadTexture(SDL_Renderer* renderer, const std::string& path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	m_Texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	if (!m_Texture) {
		printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	return true;
}

void Player::HandleInput(const glm::vec2& playerMovementDirection)
{
	if (playerMovementDirection.x != 0 || playerMovementDirection.y != 0)
		m_Velocity += glm::normalize(playerMovementDirection) * m_MovementSpeed;
}

void Player::Update(float deltaTime) {
	m_Position += m_Velocity * deltaTime;
	m_Velocity = glm::vec2();
}

void Player::Render(SDL_Renderer* renderer) const {
	SDL_Rect renderQuad = { m_Position.x, m_Position.y, m_Width, m_Height };
	SDL_RenderCopy(renderer, m_Texture, nullptr, &renderQuad);
}