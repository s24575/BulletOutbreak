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
	std::vector<std::shared_ptr<Enemy>> m_Enemies = {};
	std::vector<std::shared_ptr<Bullet>> m_Bullets;
	std::vector<std::shared_ptr<Entity>> m_Entities = {};
	std::unique_ptr<Scene> m_Scene = nullptr;
	std::unique_ptr<Camera> m_Camera = nullptr;

	CollisionManager collisionManager;
};
