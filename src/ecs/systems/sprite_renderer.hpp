#pragma once

#include <SDL2/SDL.h>

#include "../entity.hpp"
#include "../system.hpp"

struct SpriteRenderer: public System {
	void Process(Entity &entity);
	void Render(SDL_Renderer *renderer, Entity &entity);
};