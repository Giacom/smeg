#pragma once

#include <typeinfo>
#include <typeindex>

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "../service/service_container.hpp"

struct System {
	std::type_index type;
	ServiceContainer* serviceContainer;

	System();

	virtual void Process(Entity &entity);
	virtual void Render(SDL_Renderer *renderer, Entity &entity);
};