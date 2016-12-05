#pragma once

#include <memory>
#include <vector>

#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class Screen {
		public:
			Screen(ServiceContainer* serviceContainer) : serviceContainer(serviceContainer) {}

			std::vector<std::unique_ptr<System>> systems;
			std::vector<std::unique_ptr<Entity>> entities;

			ServiceContainer* serviceContainer;

			void Update();
			void Render(OpenGLRenderer &renderer);

			void AddSystem(std::unique_ptr<System> &system);
			void AddEntity(std::unique_ptr<Entity> &entity);

		private:
			static bool SortSystem(std::unique_ptr<System> &systemLeft, std::unique_ptr<System> &systemRight);
	};
}