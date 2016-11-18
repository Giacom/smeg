#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include <memory>
#include <algorithm>

#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"

namespace smeg {
	App::~App() {
		SDL_DestroyWindow(window);
		SDL_GL_DeleteContext(context);
	}

	void App::Init() {
		SDL_Log("Initialising");
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising SDL: %s", SDL_GetError());
		}

		if (TTF_Init() == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising TTF: %s", TTF_GetError());
		}

		window = SDL_CreateWindow("SMEG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 568, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GLContext context = SDL_GL_CreateContext(window);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		if (!context) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising GL Context: %s", SDL_GetError());
		}

		{
			int value = 0;
			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MAJOR_VERSION: %d\n", value);

			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MINOR_VERSION: %d\n", value);
		}

		// Services
		std::unique_ptr<Service> time = std::make_unique<Time>();
		serviceContainer.Provide<Time>(time);

		std::unique_ptr<Service> textureLibrary = std::make_unique<TextureLibrary>();
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

	Screen& App::CreateScreen() {
		screens.emplace_back(std::make_unique<Screen>(&serviceContainer));
		return *(screens.at(screens.size() - 1).get());
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
		glClear(GL_COLOR_BUFFER_BIT);
		batchRenderer.Start();
		for (auto &screen : screens) {
			screen->Render(batchRenderer);
		}
			/*
		for (auto &batch : batchRenderer.Collect()) {
			const SDL_Rect &source = batch.source;
			const SDL_Rect &dest = batch.dest;
			(source.w > 0 && source.h > 0 ? &source : NULL),
			(dest.w > 0 && dest.h > 0 ? &dest : NULL));
		}
			*/
		SDL_GL_SwapWindow(window);
	}
}