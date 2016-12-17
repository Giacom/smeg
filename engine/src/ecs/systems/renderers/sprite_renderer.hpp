#pragma once

#include <SDL2/SDL.h>
#include "../../../graphics/opengl_renderer.hpp"
#include "../../entity.hpp"
#include "../../system.hpp"

namespace smeg {

	struct SpriteRenderer: public System {

		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;

		unsigned int shaderProgram;

		const std::vector<float> vertices = { 
			// Positions          // Colors           	  // Texture Coords
			-1.0,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // Top Left 
			-1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Bottom Left
			1.0f, -1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
			1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		};

		const std::vector<unsigned short> indices = {
			0, 1, 2,
			2, 3, 0,
		};

		const char* defaultVertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"layout (location = 1) in vec3 color;\n"
			"layout (location = 2) in vec2 texCoord;\n"
			"out vec3 ourColor;\n"
			"out vec2 TexCoord;\n"
			"uniform mat4 perspective;\n"
			"uniform mat4 view;\n"
			"uniform mat4 model;\n"
			"void main()\n"
			"{\n"
			"gl_Position = perspective * view * model * vec4(position.x, position.y, position.z, 1.0);\n"
			"TexCoord = texCoord;\n"
			"ourColor = color;\n"
			"}\0";

		const char* defaultFragmentShaderSource = "#version 330 core\n"
			"in vec3 ourColor;\n"
			"in vec2 TexCoord;\n"
			"out vec4 color;\n"
			"uniform sampler2D ourTexture;\n"
			"void main()\n"
			"{\n"
			"color = texture(ourTexture, TexCoord);\n"
			"color.rgb *= ourColor;\n"
			"}\n\0";

		SpriteRenderer();
		void Initialise(OpenGLRenderer &renderer);
		void Process(Entity &entity);
		void Render(OpenGLRenderer& renderer, Entity &entity);
	};
}