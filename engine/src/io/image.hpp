#pragma once

#include "SDL.h"

namespace smeg {
	class Image {
		public:
			static SDL_Surface* Load(const char* filePath);
			static void Free(SDL_Surface* image);
	};
}