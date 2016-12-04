#pragma once

#include <SDL.h>

#include "texture.hpp"

namespace smeg {
	class BaseRenderer {
		public:
			virtual void Initialise(SDL_Window* window) = 0;
			virtual void Deinitialise() = 0;

			virtual void ClearColour(float red, float green, float blue) = 0;
			virtual void Clear() = 0;


			virtual void SwapBuffer(SDL_Window* window) = 0;

			//Texture& GenTexture();
			//void DeleteTexture(Texture& texture);
	};
}