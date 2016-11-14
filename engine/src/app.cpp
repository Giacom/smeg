#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <memory>
#include <algorithm>

#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"

namespace smeg {
	App::~App() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	void App::Init() {
		std::cout << "Initialising..." << std::endl;
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
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

	Screen* App::CreateScreen() {
		std::unique_ptr<Screen> screen = std::make_unique<Screen>();
		screen->serviceContainer = &serviceContainer;
		screens.push_back(std::move(screen));
		return screens[screens.size() - 1].get();
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
}