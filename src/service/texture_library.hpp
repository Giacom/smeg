#pragma once

#include <unordered_map>
#include <SDL2/SDL.h>

#include "../common.hpp"
#include "service.hpp"
#include "../res/texture.hpp"

typedef std::unordered_map<TextureId, SDL_Texture*> TextureMap;

struct TextureLibrary : public Service {
    private:
        TextureId uuid;
        TextureMap textureMap;

    public:
        TextureId Add(SDL_Texture* texture);
        SDL_Texture* Get(TextureId id);
        void Remove(TextureId id);
        void Clear();
};