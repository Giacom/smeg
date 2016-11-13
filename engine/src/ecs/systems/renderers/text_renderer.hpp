#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/batch_renderer.hpp"
#include "../../entity.hpp"
#include "../../system.hpp"

namespace smeg {

	struct TextRenderer: public System {
		TextRenderer();
		void Render(BatchRenderer &renderer, Entity &entity);
	};
}