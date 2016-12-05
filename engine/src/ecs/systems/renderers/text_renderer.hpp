#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/opengl_renderer.hpp"
#include "../../entity.hpp"
#include "../../system.hpp"

namespace smeg {

	struct TextRenderer: public System {
		TextRenderer();
		void Render(OpenGLRenderer &renderer, Entity &entity);
	};
}