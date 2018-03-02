#include "SDL.h"

#include <memory>
#include <algorithm>

#include "common.hpp"
#include "app.hpp"
#include "screen.hpp"
#include "service/texture_library.hpp"
#include "service/font_library.hpp"
#include "service/time.hpp"
#include "service/viewport.hpp"

#include "graphics/opengl_renderer.hpp"

namespace smeg {
	App::~App() {
		SDL_DestroyWindow(window);
	}

	void App::Init(const char* title, int windowWidth, int windowHeight) {
		SDL_Log("Initialising App");
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising SDL: %s", SDL_GetError());
		}

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		renderer.Initialise(window);
		renderer.ClearColour(0.2058f, 0.3066f, 0.4877f);
		renderer.SetViewport(windowWidth, windowHeight);

		// Services
		std::unique_ptr<Service> time = std::make_unique<Time>();
		serviceContainer.Provide<Time>(time);

		std::unique_ptr<Service> textureLibrary = std::make_unique<TextureLibrary>();
		serviceContainer.Provide<TextureLibrary>(textureLibrary);

		std::unique_ptr<Service> fontLibrary = std::make_unique<FontLibrary>();
		serviceContainer.Provide<FontLibrary>(fontLibrary);

		std::unique_ptr<Service> viewport = std::make_unique<Viewport>(windowWidth, windowHeight);
		serviceContainer.Provide<Viewport>(viewport);        

//		serviceContainer.Get<FontLibrary>().LoadFont(renderer, "res/arial.ttf", 32);
	}

	void App::Start() {
		SDL_Log("Starting App");
		bool quit = false;
		Time& time = serviceContainer.Get<Time>();

		for (auto& screen : screens) {
			screen->Initialise();
		}

		double startTime = (double)SDL_GetTicks();
		time.lastFrame = startTime - (1.0 / time.targetFrameRate);

		u64 msInterval = 1000 / time.targetFrameRate;

		double fps_frames[60];
		u64 fps_frames_size = sizeof(fps_frames) / sizeof(fps_frames[0]);
		i64 fps_index = 0;

		{
			double average_fps = 0;
			for (size_t i = 0; i < fps_frames_size; i++) {
				fps_frames[i] = (double)time.targetFrameRate;
				average_fps += fps_frames[i];
			}
			time.fps = average_fps / (double)fps_frames_size;
			//SDL_Log("average: %f", time.fps);
		}

		SDL_Log("Starting app loop.");

		while (!quit) {

			// Input
			time.ticks++;
			time.current = (double)SDL_GetTicks();

			double msDeltaTme = time.current - time.lastFrame;
			time.delta = msDeltaTme * Time::MS_TO_SEC;
			time.lastFrame = time.current;

			if (time.delta > 0) {
				fps_frames[fps_index++ % 60] = 1.0 / time.delta;
			}

			double average_fps = 0;
			for (size_t i = 0; i < fps_frames_size; i++) {
				average_fps += fps_frames[i];
			}
			time.fps = average_fps / (double)fps_frames_size;

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
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						return true;
					}
					break;
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
