#pragma once

#include <SDL.h>
#include "Player.h"
#include <memory>
#include <glm/vec2.hpp>
#include <vector>
#include "Enemy.h"
#include "Camera.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "EnemySpawner.h"

class Game {
public:
	Game();
	~Game();

	void Run();

private:
	bool Init();
	bool InitSDL();
	void HandleEvents(SDL_Event& event);
	void Update(float deltaTime);
	void Render();

	void ShootBullet(glm::vec2 startPos, glm::vec2 direction);

private:
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	bool m_ShouldQuit = false;

	std::shared_ptr<Player> m_Player = nullptr;
	std::unique_ptr<Scene> m_Scene = nullptr;
	std::unique_ptr<Camera> m_Camera = nullptr;

	std::unique_ptr<EnemySpawner> m_EnemySpawner = nullptr;
	CollisionManager m_CollisionManager;
	EntityManager& m_EntityManager;
};
