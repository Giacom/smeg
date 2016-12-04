#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/base_renderer.hpp"
#include "../../entity.hpp"
#include "../../system.hpp"

namespace smeg {

	struct SpriteRenderer: public System {
		SpriteRenderer();
		void Process(Entity &entity);
		void Render(BaseRenderer& renderer, Entity &entity);
	};
}