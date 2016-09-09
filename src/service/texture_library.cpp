#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "texture_library.hpp"

const Texture& TextureLibrary::Load(const std::string& path) {
    auto existingTexture = textureMap.find(path);
    if (existingTexture != textureMap.end()) {
        return Get(path);
    }

    textureMap[path] = std::make_unique<Texture>(path, renderer);
    return Get(path);
}

const Texture& TextureLibrary::Get(const std::string& path) {
    return *textureMap.at(path).get();
}

void TextureLibrary::Remove(const std::string& path) {
    textureMap.erase(path);
}

void TextureLibrary::Clear() {
    textureMap.clear();
}