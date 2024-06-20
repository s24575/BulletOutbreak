#include "Game.h"
#include <iostream>
#include <glm/geometric.hpp>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

Game::Game()
	: m_EntityManager(EntityManager::Instance())
{
	m_ShouldQuit = !Init();
	m_EnemySpawner = std::make_unique<EnemySpawner>(m_Renderer, m_Player);
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

	m_Player = std::make_shared<Player>(glm::vec2(), glm::vec2(1), 4.0f);
	m_EntityManager.AddEntity(m_Player);
	m_Player->LoadTexture(m_Renderer, "assets/player.png");
	m_Player->AddTag("player");
	m_Player->AddTag("collision");

	//std::shared_ptr<Enemy> enemy1 = std::make_shared<Enemy>(glm::vec2(5), glm::vec2(2), 2.0f, 200.0f);
	//m_EntityManager.AddEntity(enemy1);
	//enemy1->LoadTexture(m_Renderer, "assets/enemy.png");
	//enemy1->AddTag("enemy");
	//enemy1->AddTag("collision");

	m_Camera = std::make_unique<Camera>(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_Scene = std::make_unique<Scene>(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Scene->InitBackground(m_Renderer, "assets/grass.png", "assets/wall.png", 1);

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

	TTF_Init();

	SDL_SetRenderDrawColor(m_Renderer, 124, 252, 0, 255);

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
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				ShootBullet(glm::vec2(mouseX, mouseY));
			}
			break;
		}
	}

	glm::vec2 moveDirection = glm::vec2(0, 0);

	if (keys[SDL_SCANCODE_W]) moveDirection.y--;
	if (keys[SDL_SCANCODE_S]) moveDirection.y++;
	if (keys[SDL_SCANCODE_D]) moveDirection.x++;
	if (keys[SDL_SCANCODE_A]) moveDirection.x--;

	m_Player->HandleInput(moveDirection);
}

void Game::Update(float deltaTime)
{
	m_EnemySpawner->Update(deltaTime);

	m_EntityManager.UpdateEntities(deltaTime);

	m_CollisionManager.HandleCollisions(m_EntityManager.GetEntities());

	m_EntityManager.RemoveDeletedEntities();

	m_Camera->SetPosition(m_Player->GetPosition());
}

void Game::Render()
{
	SDL_RenderClear(m_Renderer);

	// Render scene (for now it is not an entity)
	m_Scene->Draw(m_Renderer, *m_Camera);

	m_EntityManager.DrawEntities(m_Renderer, *m_Camera);

	if (!m_Player->IsAlive())
		ShowDeathMessage();

	SDL_RenderPresent(m_Renderer);
}

void Game::ShootBullet(glm::vec2 mousePosition) {
	if (!m_Player->IsAlive())
		return;

	glm::vec2 worldPos = m_Camera->ScreenToWorld(mousePosition);

	glm::vec2 playerPosition = m_Player->GetPosition() + m_Player->GetSize() / 2.0f;
	glm::vec2 direction = glm::normalize(worldPos - playerPosition);

	auto bullet = std::make_shared<Bullet>(playerPosition, glm::vec2(0.2f), direction, 8.0f);
	bullet->AddTag("bullet");
	m_EntityManager.AddEntity(bullet);
}

void Game::ShowDeathMessage()
{
	TTF_Font* sans = TTF_OpenFont("assets/OpenSans-Bold.ttf", 24);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(sans, "You died!", { 255, 255, 255 });

	SDL_Texture* message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);

	SDL_Rect message_rect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderCopy(m_Renderer, message, NULL, &message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}
