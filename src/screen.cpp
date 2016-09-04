#include <memory>
#include <typeindex>
#include <iostream>

#include "screen.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/component.hpp"

void Screen::AddSystem(std::unique_ptr<System> &system) {
	system->serviceContainer = serviceContainer;
	systems.push_back(std::move(system));
}

void Screen::AddEntity(std::unique_ptr<Entity> &entity) {
	entities.push_back(std::move(entity));
}

void Screen::Update() {
	for (auto &system : systems) {
		for (auto &entity : entities) {
			if (entity->components.count(system->type)) {
				system->Process(*entity);
			}
		}
	}
}

void Screen::Render(SDL_Renderer *renderer) {
	for (auto &system : systems) {
		for (auto &entity : entities) {
			if (entity->components.count(system->type)) {
				system->Render(renderer, *entity);
			}
		}
	}
}
