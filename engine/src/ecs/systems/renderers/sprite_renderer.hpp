#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/opengl_renderer.hpp"
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
		void Initialise(OpenGLRenderer &renderer) override;
		void Process(Entity &entity) override;
		void Render(OpenGLRenderer& renderer, Entity &entity) override;
	};
}