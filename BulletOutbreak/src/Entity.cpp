#include "Entity.h"
#include <iostream>
#include "EntityManager.h"

Entity::Entity(glm::vec2 position, glm::vec2 size)
	: m_Position(position), m_Size(size), m_Velocity(0.0f, 0.0f), m_Acceleration()
{
}

void Entity::Update(float deltaTime) {
	m_Position += m_Velocity;
}

void Entity::Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const {
	SDL_Rect rect = { static_cast<int>(m_Position.x), static_cast<int>(m_Position.y),
					  static_cast<int>(m_Size.x), static_cast<int>(m_Size.y) };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);
}

void Entity::OnCollision(std::shared_ptr<Entity> other)
{
}

void Entity::HandleCollision(std::shared_ptr<Entity> other) {
	if (this->HasTag("collision") && other->HasTag("collision")) {
		glm::vec2 overlap = calculateOverlap(other);
		if (overlap.x != 0 && overlap.y != 0) {
			resolveCollision(other, overlap);
		}
	}
}

bool Entity::IsColliding(std::shared_ptr<Entity> other) const {
	glm::vec2 otherPos = other->GetPosition();
	glm::vec2 otherSize = other->GetSize();
	return !(m_Position.x + m_Size.x < otherPos.x || m_Position.x > otherPos.x + otherSize.x ||
		m_Position.y + m_Size.y < otherPos.y || m_Position.y > otherPos.y + otherSize.y);
}

void Entity::AddTag(const std::string& tag) {
	m_Tags.push_back(tag);
}

std::vector<std::string> Entity::GetTags()
{
	return m_Tags;
}

bool Entity::HasTag(const std::string& tag) const {
	return std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end();
}

glm::vec2 Entity::GetPosition() const {
	return m_Position;
}

glm::vec2 Entity::GetSize() const {
	return m_Size;
}

glm::vec2 Entity::GetVelocity() const {
	return m_Velocity;
}

void Entity::SetPosition(glm::vec2 position) {
	m_Position = position;
}

void Entity::SetSize(glm::vec2 size)
{
	m_Size = size;
}

void Entity::SetVelocity(glm::vec2 velocity)
{
	m_Velocity = velocity;
}

glm::vec2 Entity::calculateOverlap(std::shared_ptr<Entity> other) {
	glm::vec2 otherPos = other->GetPosition();
	glm::vec2 otherSize = other->GetSize();
	glm::vec2 overlap;

	if (m_Position.x < otherPos.x) {
		overlap.x = (m_Position.x + m_Size.x) - otherPos.x;
	}
	else {
		overlap.x = (otherPos.x + otherSize.x) - m_Position.x;
	}

	if (m_Position.y < otherPos.y) {
		overlap.y = (m_Position.y + m_Size.y) - otherPos.y;
	}
	else {
		overlap.y = (otherPos.y + otherSize.y) - m_Position.y;
	}

	overlap.x = std::max(0.0f, overlap.x);
	overlap.y = std::max(0.0f, overlap.y);

	return overlap;
}

void Entity::resolveCollision(std::shared_ptr<Entity> other, glm::vec2 overlap) {
	if (overlap.x < overlap.y) {
		float moveX = overlap.x / 2;
		if (m_Position.x < other->GetPosition().x) {
			m_Position.x -= moveX;
			other->SetPosition(glm::vec2(other->GetPosition().x + moveX, other->GetPosition().y));
		}
		else {
			m_Position.x += moveX;
			other->SetPosition(glm::vec2(other->GetPosition().x - moveX, other->GetPosition().y));
		}
	}
	else {
		float moveY = overlap.y / 2;
		if (m_Position.y < other->GetPosition().y) {
			m_Position.y -= moveY;
			other->SetPosition(glm::vec2(other->GetPosition().x, other->GetPosition().y + moveY));
		}
		else {
			m_Position.y += moveY;
			other->SetPosition(glm::vec2(other->GetPosition().x, other->GetPosition().y - moveY));
		}
	}
}
