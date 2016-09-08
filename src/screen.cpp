#include <memory>
#include <typeindex>
#include <algorithm>

#include "screen.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/component.hpp"

void Screen::AddSystem(std::unique_ptr<System> &system) {
	system->serviceContainer = serviceContainer;
	systems.emplace_back(std::move(system));
	std::sort(systems.begin(), systems.end(), Screen::SortSystem);
}

void Screen::AddEntity(std::unique_ptr<Entity> &entity) {
	entities.emplace_back(std::move(entity));
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

bool Screen::SortSystem(std::unique_ptr<System> &systemLeft, std::unique_ptr<System> &systemRight) {
	return systemLeft->executionOrder < systemRight->executionOrder;
} 
