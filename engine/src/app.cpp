#include "SDL.h"
#include <SDL_ttf.h>

#include <memory>
#include <algorithm>

#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"
#include "service/viewport.hpp"

#include "graphics/opengl_renderer.hpp"

namespace smeg {
	App::~App() {
		SDL_DestroyWindow(window);
	}

	void App::Init(int windowWidth, int windowHeight) {
		SDL_Log("Initialising App");
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising SDL: %s", SDL_GetError());
		}

		if (TTF_Init() == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising TTF: %s", TTF_GetError());
		}

		window = SDL_CreateWindow("SMEG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		renderer.Initialise(window);
        renderer.ClearColour(0.2058f, 0.3066f, 0.4877f);
		renderer.SetViewport(windowWidth, windowHeight);

		// Services
		std::unique_ptr<Service> time = std::make_unique<Time>();
		serviceContainer.Provide<Time>(time);

		std::unique_ptr<Service> textureLibrary = std::make_unique<TextureLibrary>();
		serviceContainer.Provide<TextureLibrary>(textureLibrary);

		std::unique_ptr<Service> viewport = std::make_unique<Viewport>(windowWidth, windowHeight);
		serviceContainer.Provide<Viewport>(viewport);
	}

	void App::Start() {
		SDL_Log("Starting App");
		bool quit = false;
		Time& time = serviceContainer.Get<Time>();

		for (auto& screen : screens) {
			screen->Initialise();
		}

		auto startTime = SDL_GetTicks();
		time.lastFrame = startTime;

		auto interval = 1000 / time.targetFrameRate;
		auto calculatedFps = 0;
		auto lastSecond = startTime;

		SDL_Log("Starting app loop.");

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

			renderer.CheckErrors();
		}
	}

	Screen& App::CreateScreen() {
		screens.emplace_back(std::make_unique<Screen>(&serviceContainer, &renderer));
		return *(screens.at(screens.size() - 1).get());
	}

	bool App::ProcessEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
				case SDL_QUIT:
					return true;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
						int x = event.window.data1;
						int y = event.window.data2;
						renderer.SetViewport(x, y);
						serviceContainer.Get<Viewport>().UpdateViewport(x, y);
					}
					break;
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
		renderer.Clear();

		for (auto &screen : screens) {
			screen->Render();
		}

		renderer.SwapBuffer(window);
	}
}