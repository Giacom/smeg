#pragma once

#include "SDL.h"
#include <vector>

#include "screen.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class App {
		private:
			SDL_Window* window;
			std::vector<std::unique_ptr<Screen>> screens;

			ServiceContainer serviceContainer;
            OpenGLRenderer renderer;

		public:
			App() = default;
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