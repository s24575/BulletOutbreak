#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

EntityManager& EntityManager::Instance() {
    static EntityManager instance;
    return instance;
}

void EntityManager::AddEntity(std::shared_ptr<Entity> entity) {
    m_Entities.push_back(entity);
}

void EntityManager::RemoveDeletedEntities()
{
    m_Entities.erase(std::remove_if(m_Entities.begin(), m_Entities.end(),
        [](const std::shared_ptr<Entity>& entity) { return entity->ShouldBeRemoved(); }),
        m_Entities.end());
}

void EntityManager::UpdateEntities(float deltaTime) {
    for (auto& entity : m_Entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::DrawEntities(SDL_Renderer* renderer, const Camera& camera) {
    auto& entitiesToDraw(m_Entities);

    std::sort(entitiesToDraw.begin(), entitiesToDraw.end(),
        [](const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b) {
            return a->GetDrawOrder() < b->GetDrawOrder();
        });

    for (const auto& entity : entitiesToDraw) {
        glm::vec2 entityPosition = camera.WorldToScreen(entity->GetPosition());
        entity->Draw(renderer, entityPosition, camera.GetZoom());
    }
}

std::vector<std::shared_ptr<Entity>>& EntityManager::GetEntities()
{
    return m_Entities;
}

std::shared_ptr<Entity> EntityManager::FindEntityWithTag(const std::string& tag) {
	for (const auto& entity : m_Entities) {
		for (const auto& entity_tag : entity->GetTags()) {
			if (entity_tag == tag)
				return entity;
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Entity>> EntityManager::FindEntitiesWithTag(const std::string& tag) {
	std::vector<std::shared_ptr<Entity>> taggedEntities;
	for (const auto& entity : m_Entities) {
		for (const auto& entity_tag : entity->GetTags()) {
			if (entity_tag == tag)
				taggedEntities.push_back(entity);
		}
	}
	return taggedEntities;
}
