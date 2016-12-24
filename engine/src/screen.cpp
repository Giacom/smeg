#include <memory>
#include <typeindex>
#include <algorithm>

#include "screen.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/component.hpp"
#include "service/viewport.hpp"

namespace smeg {

	void Screen::AddSystem(std::unique_ptr<System> &system) {
		system->serviceContainer = serviceContainer;

		int requiredComponents = system->types.size();

		for (auto &entity : entities) {

			int matchingComponents = 0;

			for (auto type : system->types) {
				bool hasMatchingComponent = entity->components.count(type) > 0;
				if (hasMatchingComponent) {
					matchingComponents++;
				}

				if (matchingComponents >= requiredComponents) {
					system->Register(*renderer, *entity);
					break;
				}
			}
		}

		systems.emplace_back(std::move(system));
		std::sort(systems.begin(), systems.end(), Screen::SortSystem);
	}

	void Screen::AddEntity(std::unique_ptr<Entity> &entity) {

		for (auto &system : systems) {

			int requiredComponents = system->types.size();

			int matchingComponents = 0;

			for (auto type : system->types) {
				bool hasMatchingComponent = entity->components.count(type) > 0;
				if (hasMatchingComponent) {
					matchingComponents++;
				}

				if (matchingComponents >= requiredComponents) {
					system->Register(*renderer, *entity);
					break;
				}
			}
		}

		entities.emplace_back(std::move(entity));
	}

	void Screen::Initialise() {
		for (auto &system : systems) {
			system->Initialise(*renderer);
		}
	}

	void Screen::Update() {
		for (auto &system : systems) {

			int requiredComponents = system->types.size();

			for (auto &entity : entities) {

				int matchingComponents = 0;

				for (auto type : system->types) {
					bool hasMatchingComponent = entity->components.count(type) > 0;
					if (hasMatchingComponent) {
						matchingComponents++;
					}

					if (matchingComponents >= requiredComponents) {
						system->Process(*entity);
						break;
					}
				}
			}
		}
	}

	void Screen::Render() {
		batcher.Start();
		for (auto &system :systems) {

			int requiredComponents = system->types.size();

			for (auto &entity : entities) {

				int matchingComponents = 0;

				for (auto type : system->types) {
					bool hasMatchingComponent = entity->components.count(type) > 0;
					if (hasMatchingComponent) {
						matchingComponents++;
					}

					if (matchingComponents >= requiredComponents) {
						system->Render(*renderer, batcher, *entity);
						break;
					}
				}
			}
		}

		Matrix4 view = Matrix4::Identity();	
		Matrix4 perspective = serviceContainer->Get<Viewport>().GetPerspectiveMatrix();
		batcher.Render(*renderer, view, perspective);
	}

	bool Screen::SortSystem(std::unique_ptr<System> &systemLeft, std::unique_ptr<System> &systemRight) {
		return systemLeft->executionOrder < systemRight->executionOrder;
	}
}