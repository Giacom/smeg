#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "texture.hpp"

Texture::Texture(const std::string& filePath, SDL_Renderer* renderer) {
    SDL_Surface* image = IMG_Load(filePath.c_str());
    if (!image) {
        std::cout << "ERROR: Unable to load texture image: " << filePath << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    if (!texture) {
        std::cout << "ERROR: Unable to convert texture from surface to texture: " << filePath << std::endl;
        return;
    }
    sdlTexture = texture;
}

Texture::~Texture() {
    if (sdlTexture) {
        SDL_DestroyTexture(sdlTexture);
    }
}