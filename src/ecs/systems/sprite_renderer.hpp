#pragma once

#include <typeinfo>
#include <typeindex>
#include <SDL2/SDL.h>

#include "../entity.hpp"
#include "../system.hpp"
#include "../components/sprite_component.hpp"

struct SpriteRenderer: public System {
	SpriteRenderer();
	void Process(Entity &entity);
	void Render(SDL_Renderer *renderer, Entity &entity);
};