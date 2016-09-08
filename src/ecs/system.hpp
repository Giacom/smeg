#pragma once

#include <typeinfo>
#include <typeindex>

#include <SDL2/SDL.h>
#include "entity.hpp"
#include "../service/service_container.hpp"

struct System {

	static const int EARLY = -100;
	static const int NORMAL = 0;
	static const int LATE = 100;


	std::type_index type;
	ServiceContainer* serviceContainer;
	int executionOrder = NORMAL;

	System();

	virtual void Process(Entity &entity);
	virtual void Render(SDL_Renderer *renderer, Entity &entity);
};