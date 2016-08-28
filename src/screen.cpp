#include <memory>

#include "screen.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/component.hpp"

void Screen::AddSystem(std::unique_ptr<System> &system) {
	systems.push_back(std::move(system));
}

void Screen::AddEntity(std::unique_ptr<Entity> &entity) {
	entities.push_back(std::move(entity));
}

void Screen::Update() {
	for (auto &entity : entities) {
		for (auto &component : entity->components) {
			for (auto &system : systems) {
				if (component->type == system->type) {
					system->Process(*entity);
				}
			}
		}
	}
}

void Screen::Render(SDL_Renderer *renderer) {
	for (auto &entity : entities) {
		for (auto &component : entity->components) {
			for (auto &system : systems) {
				if (component->type == system->type) {
					system->Render(renderer, *entity);
				}
			}
		}
	}
}
