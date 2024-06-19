#pragma once

#include <SDL_image.h>
#include <string>
#include <glm/vec2.hpp>
#include <memory>
#include "Camera.h"
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy(glm::vec2 position, glm::vec2 size, float movementSpeed, float healthPoints);
	~Enemy();

	void LoadTexture(SDL_Renderer* renderer, const std::string& path);
	void Update(float deltaTime);
	void OnCollision(std::shared_ptr<Entity> other) override;
	void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const override;

	void TakeDamage(float damage);

private:
	float m_HealthPoints;
	float m_MovementSpeed;

	SDL_Texture* m_Texture = nullptr;
};
