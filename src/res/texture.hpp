#pragma once

#include <string>
#include <SDL2/SDL.h>

struct Texture {
    SDL_Texture* sdlTexture;
    int w, h;

    Texture(const std::string& filePath, SDL_Renderer* renderer);
    ~Texture();
};