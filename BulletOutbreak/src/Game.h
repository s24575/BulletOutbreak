#pragma once

#include <SDL.h>
#include "Player.h"
#include <memory>
#include <glm/vec2.hpp>

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

private:
	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	bool m_ShouldQuit = false;

	std::unique_ptr<Player> m_Player;
};