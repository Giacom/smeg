#pragma once

#include "ecs/system.hpp"

namespace smeg {

	struct FpsDisplay: public System {
		FpsDisplay();
		void Initialise(OpenGLRenderer &renderer);
		void Register(OpenGLRenderer &renderer, Entity &entity);
		void Deregister(OpenGLRenderer &renderer, Entity &entity);
		void Process(Entity &entity);
		void Render(OpenGLRenderer& renderer, SpriteBatchRenderer& batcher, Entity &entity);
	};
}