#pragma once

#include <SDL.h>
#include "graphics/opengl_renderer.hpp"
#include "ecs/entity.hpp"
#include "ecs/system.hpp"

namespace smeg {

	struct TextRenderer: public System {
		TextRenderer();
		void Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity);
	};
}