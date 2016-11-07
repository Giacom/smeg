#include "batch_renderer.hpp"
#include <algorithm>

void BatchRenderer::Start() {
    batches.clear();
}

void BatchRenderer::BatchTexture(Texture &texture, SDL_Rect source, SDL_Rect dest, int layer) {
    batches.emplace_back(&texture, source, dest, layer);
}

std::vector<struct Batch>& BatchRenderer::Collect() {
    std::sort(batches.begin(), batches.end(), [](const struct Batch &lhs, const struct Batch &rhs) {
        return lhs.layer < rhs.layer;
    });
    return batches;
}

