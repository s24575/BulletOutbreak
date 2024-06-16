#include "Camera.h"
#include <algorithm>
#include <iostream>

Camera::Camera(int screenWidth, int screenHeight)
	: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight), m_Position(glm::vec2()), m_Zoom(1.5f) {}

void Camera::SetPosition(glm::vec2 position)
{
	m_Position = position;
}

void Camera::SetZoom(float zoom) {
    m_Zoom = std::clamp(zoom, 0.9f, 2.5f);
}

float Camera::GetZoom() const {
    return m_Zoom;
}

glm::vec2 Camera::WorldToScreen(const glm::vec2& worldPos) const {
    glm::vec2 screenCenter(m_ScreenWidth / 2.0f, m_ScreenHeight / 2.0f);
    glm::vec2 offset = (worldPos - m_Position) * m_Zoom;
    return screenCenter + offset;
}