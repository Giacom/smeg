#pragma once

#include "SDL.h"
#include <vector>

#include "screen.hpp"
#include "graphics/opengl_renderer.hpp"
#include "graphics/render_pipeline.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class App {
		private:
			SDL_Window* window;
			std::vector<std::unique_ptr<Screen>> screens;

			ServiceContainer serviceContainer;
            OpenGLRenderer renderer;
			RenderPipeline pipeline;

		public:
			App() = default;
			~App();
			void Init(const char* title = "SMEG", i32 windowWidth = 512, i32 windowHeight = 512);
			void Start();
			Screen& CreateScreen();

		private:
			bool ProcessEvents();
			void Update();
			void Render();
	};
}