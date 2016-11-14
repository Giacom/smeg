#pragma once

#include <SDL2/SDL.h>

#include "texture.hpp"

namespace smeg {

	struct Batch {
		Texture *texture;
		SDL_Rect source;
		SDL_Rect dest;
		int layer;

		Batch(Texture *texture, SDL_Rect source, SDL_Rect dest, int layer) :
			texture(texture), source(source), dest(dest), layer(layer) {}
	};
}