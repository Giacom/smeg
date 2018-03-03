#pragma once

#include "SDL.h"
#include "graphics/opengl_renderer.hpp"
#include "ecs/components/text.hpp"
#include "ecs/entity.hpp"
#include "ecs/system.hpp"

namespace smeg {

	struct TextRenderer: public System {
		u32 vbo;
		u32 vao;
		u32 ebo;

		u32 shaderProgram;

		std::string vertexShaderFilePath;
		std::string fragmentShaderFilePath;

		TextRenderer(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void Initialise();
		void Register(Entity &entity);
		void Deregister(Entity &entity);
		void Process(Entity &entity);
		void Render(Entity &entity);

		void UpdateTextMesh(Text &text);
	};
}