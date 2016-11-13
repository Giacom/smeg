#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace smeg {

    struct Texture {
        struct SDL_Texture *sdlTexture;
        int w, h;

        Texture(struct SDL_Texture *texture);
        ~Texture();
    };
}