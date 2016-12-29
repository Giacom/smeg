#pragma once

#include "SDL.h"

namespace smeg {
	class Image {
		public:
			static SDL_Surface* LoadFromFile(const char* filePath);
			static SDL_Surface* LoadFromMem(unsigned char* data, int width, int height, int format);
			static void Free(SDL_Surface* image);
	};
}