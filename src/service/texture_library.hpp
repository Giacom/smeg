#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

#include "service.hpp"
#include "../res/texture.hpp"

typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TextureMap;

struct TextureLibrary : public Service {
    private:
        TextureMap textureMap;
        SDL_Renderer* renderer;

    public:
        TextureLibrary(SDL_Renderer* renderer) : Service(), renderer(renderer) {}
        const Texture& Load(const std::string& path);
        const Texture& Get(const std::string& path);
        void Remove(const std::string& path);
        void Clear();
};