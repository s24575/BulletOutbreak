#pragma once

#include <SDL_image.h>
#include <string>
#include <glm/vec2.hpp>
#include <memory>
#include "Camera.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(glm::vec2 position, glm::vec2 size, float movementSpeed);
	~Player();

	void LoadTexture(SDL_Renderer* renderer, const std::string& path);
	void HandleInput(const glm::vec2& playerMovementDirection);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const override;

	void TakeDamage(float damage);

private:
	glm::vec2 m_MoveForce = glm::vec2();
	glm::vec2 m_ForceToApply = glm::vec2();
	float m_MovementSpeed;
	float m_HealthPoints = 200.0f;

	SDL_Texture* m_Texture = nullptr;
};
