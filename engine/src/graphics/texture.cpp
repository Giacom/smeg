#include <SDL2/SDL.h>
#include "texture.hpp"

namespace smeg {

	Texture::Texture(SDL_Texture *texture) : sdlTexture(texture) {}

	Texture::~Texture() {
		if (sdlTexture) {
			SDL_DestroyTexture(sdlTexture);
		}
	}
}