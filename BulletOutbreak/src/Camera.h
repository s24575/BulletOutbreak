#pragma once

#include <glm/vec2.hpp>


class Camera {
public:
	Camera(int screenWidth, int screenHeight);

	glm::vec2 GetPosition() const;
	float GetZoom() const;
	void SetPosition(glm::vec2 position);
	void SetZoom(float zoom);

	glm::vec2 WorldToScreen(const glm::vec2& worldPos) const;
	glm::vec2 ScreenToWorld(glm::vec2 screenPos) const;

private:
	glm::vec2 m_Position;
	float m_Zoom;

	int m_ScreenWidth;
	int m_ScreenHeight;
};
