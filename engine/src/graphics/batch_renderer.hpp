#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "batch.hpp"
#include "texture.hpp"

namespace smeg {

    struct BatchRenderer {
        std::vector<Batch> batches;

        void Start();
        void BatchTexture(Texture &texture, SDL_Rect source, SDL_Rect dest, int layer);
        std::vector<struct Batch>& Collect();
    };
}