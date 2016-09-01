#pragma once

#include <typeinfo>
#include <typeindex>

#include <SDL2/SDL.h>
#include "entity.hpp"

struct System {
	std::type_index type;

	System();

	virtual void Process(Entity &entity);
	virtual void Render(SDL_Renderer *renderer, Entity &entity);
};