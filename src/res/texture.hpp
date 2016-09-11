#pragma once

#include <SDL2/SDL.h>
#include <string>

struct Texture {
    struct SDL_Texture* sdlTexture;
    int w, h;

    Texture(struct SDL_Texture *texture);
    ~Texture();
};