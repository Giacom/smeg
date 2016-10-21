#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <algorithm>

#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"
#include "ecs/systems/renderers/sprite_renderer.hpp"
#include "ecs/systems/renderers/text_renderer.hpp"
#include "ecs/systems/debug/fps_display.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/sprite.hpp"
#include "ecs/components/text.hpp"
#include "ecs/components/debug/fps.hpp"

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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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

	std::unique_ptr<System> fpsDisplay = std::make_unique<FpsDisplay>();
	mainScreen->AddSystem(fpsDisplay);

	// Components
	// FPS Display
	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		TTF_Font *font = TTF_OpenFont("res/arial.ttf", 24);
		if (!font) {
			std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		} else {
			std::cout << "Font found!" << std::endl;
		}

		std::unique_ptr<Component> transform = std::make_unique<Transform>(20, 10);
		std::unique_ptr<Component> text = std::make_unique<Text>(std::string(""), font, 100, SDL_Color { 0x0, 0x77, 0x0, 0xFF });
		std::unique_ptr<Component> fps = std::make_unique<Fps>();

		entity->AddComponent(transform);
		entity->AddComponent(text);
		entity->AddComponent(fps);
		mainScreen->AddEntity(entity);
	}

	// Ducks
	for (int i = 0; i < 3; ++i) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(0, (i * 64) + i);
		std::unique_ptr<Component> sprite = std::make_unique<Sprite>(std::string("res/duck.png"), 128, 128, 100 - i);

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		mainScreen->AddEntity(entity);
	}

	screens.push_back(std::move(mainScreen));
}

void App::Start() {
	bool quit = false;
	Time& time = serviceContainer.Get<Time>();

	auto startTime = SDL_GetTicks();
	time.lastFrame = startTime;

	auto interval = 1000 / time.targetFrameRate;
	auto calculatedFps = 0;
	auto lastSecond = startTime;

	while (!quit) {
		// Input
		time.ticks++;
		time.current = SDL_GetTicks();

		auto dt = time.current - time.lastFrame;
		time.delta = (double)dt * Time::MS_TO_SEC;

		if (dt < interval) {
			SDL_Delay(interval - dt);
			continue;
		}
		
		time.lastFrame = time.current;
		calculatedFps += 1;

		if (time.current - lastSecond > 1000) {
			time.fps = calculatedFps;
			lastSecond = time.current;
			calculatedFps = 0;
		}

		quit = ProcessEvents();
		Update();
		Render();
	}
}

bool App::ProcessEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_QUIT:
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
	batchRenderer.Start();
	for (auto &screen : screens) {
		screen->Render(batchRenderer);
	}
	for (auto &batch : batchRenderer.Collect()) {
		const SDL_Rect &source = batch.source;
		const SDL_Rect &dest = batch.dest;
		SDL_RenderCopy(renderer, batch.texture->sdlTexture,
		(source.w > 0 && source.h > 0 ? &source : NULL),
		(dest.w > 0 && dest.h > 0 ? &dest : NULL));
	}
	SDL_RenderPresent(renderer);
}