#include <SDL2/SDL.h>
#include "texture_library.hpp"

TextureId TextureLibrary::Add(SDL_Texture* texture) {
    auto textureId = uuid++;
    textureMap[textureId] = texture;
    return textureId;
}

SDL_Texture* TextureLibrary::Get(TextureId id) {
    return textureMap.at(id);
}

void TextureLibrary::Remove(TextureId id) {
    SDL_DestroyTexture(Get(id));
    textureMap.erase(id);
}

void TextureLibrary::Clear() {
    for (auto& keyValue : textureMap) {
        SDL_DestroyTexture(keyValue.second);
    }
    textureMap.clear();
}