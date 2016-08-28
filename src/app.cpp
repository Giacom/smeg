#include <SDL2/SDL.h>

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

	Screen mainScreen;

	DrawSystem drawSystem;
	mainScreen.AddSystem(drawSystem);

	Entity testEntity;
	SpriteComponent spriteComponent(12, 12, 30, 30);
	testEntity.components.push_back(spriteComponent);

	mainScreen.AddEntity(testEntity);

	screens.push_back(mainScreen);
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
		screen.Update();
	}
}

void App::Render() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
	for (auto &screen : screens) {
		screen.Render(renderer);
	}
	SDL_RenderPresent(renderer);
}