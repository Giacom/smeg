#pragma once

#include <SDL2/SDL.h>

#include "component_type.hpp"
#include "entity.hpp"

struct System {
	ComponentType type;

	virtual void Process(Entity &entity);
	virtual void Render(SDL_Renderer *renderer, Entity &entity);
};