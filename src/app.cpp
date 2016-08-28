#include <SDL2/SDL.h>
#include <memory>

#include "app.hpp"
#include "screen.hpp"
#include "ecs/systems/draw_system.hpp"
#include "ecs/components/sprite_component.hpp"

App::~App() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void App::Init() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 568, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	std::unique_ptr<Screen> mainScreen = std::make_unique<Screen>();

	std::unique_ptr<System> drawSystem = std::make_unique<DrawSystem>();
	drawSystem->type = 1;

	mainScreen->AddSystem(drawSystem);

	for (int i = 0; i < 5; ++i) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> spriteComponent = std::make_unique<SpriteComponent>(0, (i * 32) + i, 32, 32);
		spriteComponent->type = 1;

		entity->AddComponent(spriteComponent);
		mainScreen->AddEntity(entity);
	}

	screens.push_back(std::move(mainScreen));
}

void App::Start() {
	bool quit = false;
	SDL_Event event;

	while (!quit) {
		// Input
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					return;
			}
		}

		Update();

		Render();
	}
}

void App::Update() {
	for(auto &screen : screens) {
		screen->Update();
	}
}

void App::Render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	for (auto &screen : screens) {
		screen->Render(renderer);
	}
	SDL_RenderPresent(renderer);
}