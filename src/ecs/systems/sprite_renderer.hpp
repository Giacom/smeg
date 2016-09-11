#pragma once

#include <SDL2/SDL.h>
#include "../entity.hpp"
#include "../system.hpp"

struct SpriteRenderer: public System {
	SpriteRenderer();
	void Process(Entity &entity);
	void Render(BatchRenderer &renderer, Entity &entity);
};