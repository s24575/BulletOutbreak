#pragma once

#include <glm/vec2.hpp>
#include <SDL_render.h>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

class Entity {
public:
    Entity(glm::vec2 position, glm::vec2 size);

    virtual void Update(float deltaTime);
    virtual void Draw(SDL_Renderer* renderer, const glm::vec2& screenPos, float zoom) const;
    virtual void OnCollision(std::shared_ptr<Entity> other);
    virtual void HandleCollision(std::shared_ptr<Entity> other);
    bool IsColliding(std::shared_ptr<Entity> other) const;

    void AddTag(const std::string& tag);
    void RemoveTag(const std::string& tag);
    std::vector<std::string> GetTags() const;
    bool HasTag(const std::string& tag) const;

    void MarkForRemoval() { m_ShouldBeRemoved = true; }
    bool ShouldBeRemoved() const { return m_ShouldBeRemoved; }

    int GetDrawOrder() const { return m_DrawOrder; }

    glm::vec2 GetPosition() const;
    glm::vec2 GetSize() const;
    glm::vec2 GetVelocity() const;
    void SetPosition(glm::vec2 pos);
    void SetSize(glm::vec2 pos);
    void SetVelocity(glm::vec2 pos);

protected:
    glm::vec2 m_Size;
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    glm::vec2 m_Acceleration;

    std::string m_Name;
    std::vector<std::string> m_Tags;
    uint32_t m_DrawOrder = 0;

    bool m_ShouldBeRemoved = false;

    glm::vec2 calculateOverlap(std::shared_ptr<Entity> other);
    void resolveCollision(std::shared_ptr<Entity> other, glm::vec2 overlap);
};
