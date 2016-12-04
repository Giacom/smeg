#pragma once

#include <SDL.h>
#include "../base_renderer.hpp"

namespace smeg {

	class OpenGLRenderer : public BaseRenderer {
        private:
	        SDL_GLContext context;

        public:
            void Initialise(SDL_Window* window) override;
            void Deinitialise() override;

            void ClearColour(float red, float green, float blue) override;
            void Clear() override;

            void SwapBuffer(SDL_Window* window) override;
	};
}
