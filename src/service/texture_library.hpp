#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

#include "service.hpp"
#include "../res/texture.hpp"

typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TextureMap;

struct TextureLibrary : public Service {
    static const std::string filePrefix;
    static const std::string resPrefix;
    
    private:
        TextureMap textureMap;
        SDL_Renderer* renderer;


    public:
        TextureLibrary(SDL_Renderer* renderer) : Service(), renderer(renderer) {}
        Texture& LoadFile(const std::string& path);
        Texture& Get(const std::string& path);
        void Cache(const std::string& key, SDL_Surface *image);
        void Remove(const std::string& path);
        void Clear();
};