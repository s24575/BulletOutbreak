#include "EnemySpawner.h"
#include <glm/geometric.hpp>
#include "Enemy.h"

EnemySpawner::EnemySpawner(SDL_Renderer* renderer, std::shared_ptr<Player> player)
    : m_Renderer(renderer), m_Player(player), m_PositionDistribution(-20.0f, 20.0f), m_SpeedDistribution(1.0f, 3.0f)
{
    std::random_device rd;
    m_RandomEngine.seed(rd());
}

void EnemySpawner::Update(float deltaTime) {
    m_CurrentSpawnTime += deltaTime;
    if (m_CurrentSpawnTime >= m_SpawnInterval) {
        SpawnEnemy();
        m_CurrentSpawnTime = 0.0f;
    }
}

void EnemySpawner::SpawnEnemy() {
    glm::vec2 playerPos = m_Player->GetPosition();
    glm::vec2 enemyPos = playerPos;
    float distance = 0.0f;

    while (distance < 10.0f) {
        enemyPos.x = playerPos.x + m_PositionDistribution(m_RandomEngine);
        enemyPos.y = playerPos.y + m_PositionDistribution(m_RandomEngine);
        distance = glm::distance(playerPos, enemyPos);
    }

    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(enemyPos, glm::vec2(2.0f), m_SpeedDistribution(m_RandomEngine), 100.0f);
    enemy->LoadTexture(m_Renderer, "assets/enemy.png");
    enemy->AddTag("enemy");
    enemy->AddTag("collision");

    EntityManager::Instance().AddEntity(enemy);
}
