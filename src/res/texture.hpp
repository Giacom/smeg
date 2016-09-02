#pragma once

#include <SDL2/SDL.h>
#include "../common.hpp"

struct Texture {
    TextureId id;
    int w, h;

    Texture(TextureId id);
};