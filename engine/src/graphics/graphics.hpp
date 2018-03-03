#pragma once

#include "service/viewport.hpp"
#include "opengl_renderer.hpp"
#include "common.hpp"
#include "math/vector2.hpp"

namespace smeg {

	class Graphics {
		private:
			OpenGLRenderer* renderer;
			Viewport* viewport;

			ProgramID defaultProgram;
			ProgramID activeProgram;

			VboID vbo;
			VaoID vao;
			EboID ebo;

			static constexpr usize verticesLength = 6 * (3 + 3 + 2);

			const char* const defaultShaderFrag = 
			R"(
			#version 330 core

			in vec3 ourColor;
			in vec2 TexCoord;

			out vec4 color;

			uniform sampler2D ourTexture;

			void main()
			{
				color = texture(ourTexture, TexCoord);
				color.rgb *= ourColor;
			}

			)";

			const char* const defaultShaderVert =
				R"(
			#version 330 core

			layout (location = 0) in vec3 position;
			layout (location = 1) in vec3 color;
			layout (location = 2) in vec2 texCoord;

			out vec3 ourColor;
			out vec2 TexCoord;

			uniform mat4 perspective;
			//uniform mat4 view;
			//uniform mat4 model;

			void main()
			{
				gl_Position = perspective * vec4(position.x, position.y, position.z, 1.0);
				TexCoord = texCoord;
				ourColor = color;
			}

			)";

		public:
			void Initialise(OpenGLRenderer* renderer, Viewport* viewport);
			void SetActiveProgram(ProgramID program);
			void DrawTexture(const Texture& texture, Vector2 position);
			Texture LoadTexture(const SDL_Surface* image);
	};
}