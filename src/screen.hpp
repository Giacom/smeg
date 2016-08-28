#pragma once

#include <vector>

#include "ecs/system.hpp"
#include "ecs/entity.hpp"

struct Screen {
	std::vector<System> systems;
	std::vector<Entity> entities;

	void Update();
	void Render(SDL_Renderer *renderer);

	void AddSystem(System system);
	void AddEntity(Entity entity);
};