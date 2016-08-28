
#include "screen.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/component.hpp"

void Screen::AddSystem(System system) {
	systems.push_back(system);
}

void Screen::AddEntity(Entity entity) {
	entities.push_back(entity);
}

void Screen::Update() {
	for (auto &entity : entities) {
		for (auto &component : entity.components) {
			for (auto &system : systems) {
				if (component.type == system.type) {
					system.Process(entity);
				}
			}
		}
	}
}

void Screen::Render(SDL_Renderer *renderer) {
	for (auto &entity : entities) {
		for (auto &component : entity.components) {
			for (auto &system : systems) {
				if (component.type == system.type) {
					system.Render(renderer, entity);
				}
			}
		}
	}
}
