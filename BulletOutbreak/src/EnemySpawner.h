#pragma once

#include <memory>
#include <vector>
#include <random>
#include "Entity.h"
#include "EntityManager.h"
#include "Player.h"

class EnemySpawner {
public:
    EnemySpawner(SDL_Renderer* renderer, std::shared_ptr<Player> player);

    void Update(float deltaTime);

private:
    SDL_Renderer* m_Renderer;
    std::shared_ptr<Player> m_Player;

    std::default_random_engine m_RandomEngine;
    std::uniform_real_distribution<float> m_PositionDistribution;
    std::uniform_real_distribution<float> m_SpeedDistribution;

    float m_SpawnInterval = 5.0f;
    float m_CurrentSpawnTime = 0.0f;

    void SpawnEnemy();
};

