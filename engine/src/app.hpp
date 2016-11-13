#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "screen.hpp"
#include "service/service_container.hpp"
#include "graphics/batch_renderer.hpp"

namespace smeg {
	class App {
		private:
			SDL_Window* window;
			SDL_Renderer* renderer;
			BatchRenderer batchRenderer;

			std::vector<std::unique_ptr<Screen>> screens;
			ServiceContainer serviceContainer;

		public:
			~App();
			void Init();
			void Start();
			Screen* CreateScreen();

		private:
			bool ProcessEvents();
			void Update();
			void Render();
	};
}