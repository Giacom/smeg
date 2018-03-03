#pragma once

#include "SDL.h"
#include <vector>

#include "screen.hpp"
#include "graphics/opengl_renderer.hpp"
#include "service/service_container.hpp"

namespace smeg {
	using ScreenPtr = std::unique_ptr<Screen>;
	class App {
		public:
			ServiceContainer serviceContainer;
            OpenGLRenderer renderer;

		private:
			SDL_Window* window;
			Graphics graphics;
			std::vector<ScreenPtr> screens;

		public:
			~App();
			void Init(const char* title = "SMEG", i32 windowWidth = 512, i32 windowHeight = 512);
			void Start();
			void AddScreen(ScreenPtr& screen);

		private:
			bool ProcessEvents();
			void Update();
			void Render();
	};
}