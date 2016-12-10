#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "screen.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class App {
		private:
			SDL_Window* window;
            std::unique_ptr<OpenGLRenderer> renderer;

			std::vector<std::unique_ptr<Screen>> screens;
			ServiceContainer serviceContainer;

		public:
			~App();
			void Init(int windowWidth = 512, int windowHeight = 512);
			void Start();
			Screen& CreateScreen();

		private:
			bool ProcessEvents();
			void Update();
			void Render();
	};
}