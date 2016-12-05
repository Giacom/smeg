#pragma once

#include <vector>
#include <typeinfo>
#include <typeindex>

#include <SDL2/SDL.h>

#include "entity.hpp"
#include "../service/service_container.hpp"
#include "../graphics/opengl_renderer.hpp"

namespace smeg {

	struct System {

		static const int EARLY = -100;
		static const int NORMAL = 0;
		static const int LATE = 100;

		std::vector<std::type_index> types;
		ServiceContainer* serviceContainer;
		int executionOrder = NORMAL;

		System();

        virtual void Initialise(OpenGLRenderer& renderer) = 0;
		virtual void Process(Entity &entity) = 0;
		virtual void Render(OpenGLRenderer& renderer, Entity &entity) = 0;
	};

}