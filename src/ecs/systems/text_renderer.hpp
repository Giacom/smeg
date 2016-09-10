#pragma once

#include <SDL2/SDL.h>
#include "../../graphics/batch_renderer.hpp"
#include "../entity.hpp"
#include "../system.hpp"

struct TextRenderer: public System {
	TextRenderer();
	void Process(Entity &entity);
	void Render(SDL_Renderer *sdlRenderer, BatchRenderer &renderer, Entity &entity);
};