#pragma once

#include <SDL.h>
#include "texture.hpp"

namespace smeg {

	class OpenGLRenderer {
        private:
	        SDL_GLContext context;

        public:
            void Initialise(SDL_Window* window);
            void Deinitialise();

            void ClearColour(float red, float green, float blue);
            void Clear();

            void SwapBuffer(SDL_Window* window);
            
			Texture GenTexture();
			void DeleteTexture(Texture& texture);

            unsigned int GenVertexArrays();

	};
}
