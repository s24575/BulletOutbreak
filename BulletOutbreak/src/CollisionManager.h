#pragma once
#include <memory>
#include "Entity.h"
#include <vector>

class CollisionManager {
public:
    void CheckCollision(std::shared_ptr<Entity> entity1, std::shared_ptr<Entity> entity2) {
        if (entity1->IsColliding(entity2)) {
            entity1->HandleCollision(entity2);
            entity2->HandleCollision(entity1);
            entity1->OnCollision(entity2);
            entity2->OnCollision(entity1);
        }
    }

    void HandleCollisions(std::vector<std::shared_ptr<Entity>>& entities) {
        for (size_t i = 0; i < entities.size(); ++i) {
            for (size_t j = i + 1; j < entities.size(); ++j) {
                CheckCollision(entities[i], entities[j]);
            }
        }
    }
};
