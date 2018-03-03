#pragma once

#include <vector>
#include <typeinfo>
#include <typeindex>

#include "SDL.h"

#include "entity.hpp"
#include "service/service_container.hpp"
#include "graphics/render_pipeline.hpp"

namespace smeg {

	struct System {

		static const int EARLY = -100;
		static const int NORMAL = 0;
		static const int LATE = 100;

		std::vector<std::type_index> types;
		ServiceContainer* serviceContainer;
		RenderPipeline* pipeline;

		int executionOrder = NORMAL;

        virtual void Initialise() = 0;
		
		virtual void Register(Entity &entity) = 0;
		virtual void Deregister(Entity &entity) = 0;

		virtual void Process(Entity &entity) = 0;
		virtual void Render(Entity &entity) = 0;
	};
}