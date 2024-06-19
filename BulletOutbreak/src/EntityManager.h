#pragma once

#include <vector>
#include <memory>
#include "Camera.h"
#include <SDL_render.h>
#include <string>

class Entity;

class EntityManager {
public:
    static EntityManager& Instance();

    void AddEntity(std::shared_ptr<Entity> entity);
    void RemoveDeletedEntities();
    void UpdateEntities(float deltaTime);
    void DrawEntities(SDL_Renderer* renderer, const Camera& camera);

    std::vector<std::shared_ptr<Entity>>& GetEntities();

    std::shared_ptr<Entity> FindEntityWithTag(const std::string& tag);
    std::vector<std::shared_ptr<Entity>> FindEntitiesWithTag(const std::string& tag);

private:
    EntityManager();
    ~EntityManager();

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    std::vector<std::shared_ptr<Entity>> m_Entities;
};
