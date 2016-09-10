#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <memory>

#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"
#include "ecs/systems/sprite_renderer.hpp"
#include "ecs/systems/text_renderer.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/sprite.hpp"
#include "ecs/components/text.hpp"

App::~App() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void App::Init() {
	std::cout << "Initialising..." << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cout << "Error initialising SDL: " << SDL_GetError() << std::endl;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error initialising TTF: " << TTF_GetError() << std::endl;
	}

	window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 568, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Services
	std::unique_ptr<Service> time = std::make_unique<Time>();
	serviceContainer.Provide<Time>(time);

	std::unique_ptr<Service> textureLibrary = std::make_unique<TextureLibrary>(renderer);
	serviceContainer.Provide<TextureLibrary>(textureLibrary);

	std::unique_ptr<Screen> mainScreen = std::make_unique<Screen>();
	mainScreen->serviceContainer = &serviceContainer;

	// Systems
	std::unique_ptr<System> drawSystem = std::make_unique<SpriteRenderer>();
	mainScreen->AddSystem(drawSystem);

	std::unique_ptr<System> textDrawSystem = std::make_unique<TextRenderer>();
	mainScreen->AddSystem(textDrawSystem);


	// Components
	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		TTF_Font *font = TTF_OpenFont("res/arial.ttf", 24);
		if (!font) {
			std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		} else {
			std::cout << "Font found!" << std::endl;
		}

		std::unique_ptr<Component> transform = std::make_unique<Transform>(20, 10);
		std::unique_ptr<Component> text = std::make_unique<Text>(std::string("Hello world!"), font);

		entity->AddComponent(transform);
		entity->AddComponent(text);
		mainScreen->AddEntity(entity);
	}

	for (int i = 0; i < 5; ++i) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(0, (i * 32) + i);
		std::unique_ptr<Component> sprite = std::make_unique<Sprite>(std::string("res/duck.png"), 32, 32);

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		mainScreen->AddEntity(entity);
	}

	screens.push_back(std::move(mainScreen));
}

void App::Start() {
	bool quit = false;
	Time& gameTime = serviceContainer.Get<Time>();

	while (!quit) {
		// Input
		gameTime.current = SDL_GetTicks();
		gameTime.delta = (float)(gameTime.current - gameTime.lastFrame) * 0.001;
		
		quit = ProcessEvents();
		Update();
		Render();

		gameTime.lastFrame = gameTime.current;
	}
}

bool App::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				return true;
			case SDL_KEYDOWN:
				return true;	
		}
	}
	return false;
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