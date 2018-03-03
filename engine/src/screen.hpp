#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "graphics/render_pipeline.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class Screen {
		public:
			Screen(ServiceContainer* serviceContainer, RenderPipeline* pipeline) : serviceContainer(serviceContainer), pipeline(pipeline) {}

			std::vector<std::unique_ptr<System>> systems;
			std::vector<std::unique_ptr<Entity>> entities;

			ServiceContainer* serviceContainer;
			RenderPipeline* pipeline;

			void Initialise();
			void Update();
			void Render();

			void AddSystem(std::unique_ptr<System> &system);
			void AddEntity(std::unique_ptr<Entity> &entity);

		private:
			static bool SortSystem(std::unique_ptr<System> &systemLeft, std::unique_ptr<System> &systemRight);
	};
}