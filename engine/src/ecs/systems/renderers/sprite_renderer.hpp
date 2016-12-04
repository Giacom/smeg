#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/base_renderer.hpp"
#include "../../entity.hpp"
#include "../../system.hpp"

namespace smeg {

	struct SpriteRenderer: public System {

        unsigned int VBO;
        static constexpr float vertices[] = { 
            // Pos      // Tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

		SpriteRenderer();
        void Initialise(BaseRenderer &renderer) override;
		void Process(Entity &entity) override;
		void Render(BaseRenderer& renderer, Entity &entity) override;
	};
}