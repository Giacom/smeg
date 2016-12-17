#pragma once

#include <vector>
#include <typeinfo>
#include <typeindex>

#include <SDL2/SDL.h>

#include "entity.hpp"
#include "service/service_container.hpp"
#include "graphics/sprite_batch_renderer.hpp"

namespace smeg {

	struct System {

		static const int EARLY = -100;
		static const int NORMAL = 0;
		static const int LATE = 100;

		std::vector<std::type_index> types;
		ServiceContainer* serviceContainer;
		int executionOrder = NORMAL;

        virtual void Initialise(OpenGLRenderer& renderer) = 0;
		virtual void Process(Entity &entity) = 0;
		virtual void Render(OpenGLRenderer& renderer, SpriteBatchRenderer& batcher, Entity &entity) = 0;
	};
}