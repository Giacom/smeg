#pragma once

#include <string>

#include "graphics/opengl_renderer.hpp"
#include "ecs/entity.hpp"
#include "ecs/system.hpp"
#include "ecs/components/sprite.hpp"

namespace smeg {

	class SpriteRenderer: public System {

		public:
			u32 shaderProgram;

			std::string vertexShaderFilePath;
			std::string fragmentShaderFilePath;

			SpriteRenderer(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

			void Initialise();
			void Register(Entity &entity);
			void Deregister(Entity &entity);
			void Process(Entity &entity);
			void Render(Entity &entity);

		private:
			void UpdateRenderData(Sprite& sprite);
	};
}