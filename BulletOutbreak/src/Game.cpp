#include "Game.h"
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

Game::Game()
{
	m_ShouldQuit = !Init();
}

Game::~Game()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

bool Game::Init() {
	if (!InitSDL())
		return false;

	m_Player = std::make_unique<Player>();
	m_Player->LoadTexture(m_Renderer, "assets/player.png");

	std::unique_ptr<Enemy> enemy1 = std::make_unique<Enemy>();
	enemy1->m_Position = glm::vec2(200, 200);
	enemy1->LoadTexture(m_Renderer, "assets/enemy.png");
	m_Enemies.push_back(std::move(enemy1));

	m_Camera = std::make_unique<Camera>(SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void Game::Run() {
	Uint32 lastTime = SDL_GetTicks();
	SDL_Event event;
	while (!m_ShouldQuit) {
		Uint32 currentTime = SDL_GetTicks();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		HandleEvents(event);
		Update(deltaTime);
		Render();
	}
}

bool Game::InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("BulletOutbreak", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (m_Window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	if (m_Renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	std::cout << "Initalized SDL\n";

	return true;
}

void Game::HandleEvents(SDL_Event& event)
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_ShouldQuit = true;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0) {
				m_Camera->SetZoom(m_Camera->GetZoom() * 1.1f);
			}
			else if (event.wheel.y < 0) {
				m_Camera->SetZoom(m_Camera->GetZoom() * 0.9f);
			}
			break;
		}
	}

	glm::vec2 playerMovementDirection = glm::vec2(0, 0);

	if (keys[SDL_SCANCODE_W]) playerMovementDirection.y--;
	if (keys[SDL_SCANCODE_S]) playerMovementDirection.y++;
	if (keys[SDL_SCANCODE_D]) playerMovementDirection.x++;
	if (keys[SDL_SCANCODE_A]) playerMovementDirection.x--;

	m_Player->HandleInput(playerMovementDirection);
}

void Game::Update(float deltaTime)
{
	m_Player->Update(deltaTime);
	m_Camera->SetPosition(m_Player->GetPosition());
}

void Game::Render()
{
	SDL_RenderClear(m_Renderer);

	// Render player
	glm::vec2 playerScreenPos = m_Camera->WorldToScreen(m_Player->GetPosition());
	m_Player->Draw(m_Renderer, playerScreenPos, m_Camera->GetZoom());

	// Render enemies
	for (const auto& enemy : m_Enemies) {
		glm::vec2 enemyScreenPos = m_Camera->WorldToScreen(enemy->m_Position);
		enemy->Draw(m_Renderer, enemyScreenPos, m_Camera->GetZoom());
	}

	SDL_RenderPresent(m_Renderer);
}