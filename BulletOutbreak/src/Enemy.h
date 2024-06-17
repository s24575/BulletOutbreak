#pragma once

#include <SDL_image.h>
#include <string>
#include <glm/vec2.hpp>
#include <memory>
#include "Camera.h"
#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy(glm::vec2 position, glm::vec2 size, float movementSpeed);
	~Enemy();

	void LoadTexture(SDL_Renderer* renderer, const std::string& path);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const;

private:
	float m_MovementSpeed;

	SDL_Texture* m_Texture = nullptr;
};
