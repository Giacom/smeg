#pragma once

#include "graphics/sprite_batch_renderer.hpp"

#include <string>

#include "graphics/opengl_renderer.hpp"
#include "ecs/entity.hpp"
#include "ecs/system.hpp"
#include "ecs/components/sprite.hpp"

namespace smeg {

	class SpriteRenderer: public System {

		public:
			unsigned int shaderProgram;

			std::string vertexShaderFilePath;
			std::string fragmentShaderFilePath;

			SpriteRenderer(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

			void Initialise(OpenGLRenderer &renderer);
			void Register(OpenGLRenderer &renderer, Entity &entity);
			void Deregister(OpenGLRenderer &renderer, Entity &entity);
			void Process(Entity &entity);
			void Render(OpenGLRenderer& renderer, SpriteBatchRenderer& batcher, Entity &entity);

		private:
			void UpdateRenderData(OpenGLRenderer &renderer, Sprite& sprite);
	};
}