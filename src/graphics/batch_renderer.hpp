#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "batch.hpp"
#include "../res/texture.hpp"

struct BatchRenderer {
    std::vector<Batch> batches;

    void Start();
    void Batch(Texture &texture, SDL_Rect source, SDL_Rect dest, int layer);
    std::vector<struct Batch>& Collect();
};