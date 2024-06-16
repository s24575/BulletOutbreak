#pragma once

#include <SDL_image.h>
#include <string>
#include <glm/vec2.hpp>
#include <memory>
#include "Camera.h"

class Enemy {
public:
	Enemy();
	~Enemy();

	void LoadTexture(SDL_Renderer* renderer, const std::string& path);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const;

public:
	glm::vec2 m_Velocity;
	glm::vec2 m_Position;
	float m_MovementSpeed;
	float m_Width, m_Height;

	SDL_Texture* m_Texture;
};