#pragma once

#include <SDL_image.h>
#include <string>
#include <glm/vec2.hpp>

class Player {
public:
	Player();
	~Player();

	bool LoadTexture(SDL_Renderer* renderer, const std::string& path);
	void HandleInput(const glm::vec2& playerMovementDirection);
	void Update(float deltaTime);
	void Render(SDL_Renderer* renderer) const;

public:
	glm::vec2 m_Velocity;
	glm::vec2 m_Position;
	float m_MovementSpeed;
	float m_Width, m_Height;

	SDL_Texture* m_Texture;
};