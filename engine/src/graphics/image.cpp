#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

namespace smeg {
	SDL_Surface* Image::Load(const char* filePath) {

		int width, height, orig_format;
		unsigned char* data = stbi_load(filePath, &width, &height, &orig_format, 0);
		if(data == NULL) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading image failed: %s", stbi_failure_reason());
			throw;
		}

		// Set up the pixel format color masks for RGB(A) byte arrays.
		// Only STBI_rgb (3) and STBI_rgb_alpha (4) are supported here!
		Uint32 rmask, gmask, bmask, amask;
		#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		int shift = (orig_format == STBI_rgb) ? 8 : 0;
		rmask = 0xff000000 >> shift;
		gmask = 0x00ff0000 >> shift;
		bmask = 0x0000ff00 >> shift;
		amask = 0x000000ff >> shift;
		#else // little endian, like x86
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = (orig_format == STBI_rgb) ? 0 : 0xff000000;
		#endif

		int depth, pitch;
		if (orig_format == STBI_rgb) {
			depth = 24;
			pitch = 3*width; // 3 bytes per pixel * pixels per row
		} else { // STBI_rgb_alpha (RGBA)
			depth = 32;
			pitch = 4*width;
		}

		SDL_Surface* surf = SDL_CreateRGBSurfaceFrom((void*)data, width, height, depth, pitch,
													rmask, gmask, bmask, amask);

		if (surf == NULL) {
			SDL_Log("Creating surface failed: %s", SDL_GetError());
			stbi_image_free(data);
			throw;
		}

		// Turn off the prealloc flag so it Will make SDL_FreeSurface free the image data
		surf->flags &= ~SDL_PREALLOC;

		return surf;
	}
};