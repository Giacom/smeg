#pragma once

#include <memory>
#include <vector>

#include "ecs/system.hpp"
#include "ecs/entity.hpp"

struct Screen {
	std::vector<std::unique_ptr<System>> systems;
	std::vector<std::unique_ptr<Entity>> entities;

	void Update();
	void Render(SDL_Renderer *renderer);

	void AddSystem(std::unique_ptr<System> &system);
	void AddEntity(std::unique_ptr<Entity> &entity);
};