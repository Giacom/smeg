#pragma once

#include <SDL.h>
#include <vector>

#include "texture.hpp"
#include "opengl.hpp"
#include "../math/matrix4.hpp"

namespace smeg {

	class OpenGLRenderer {
		private:
			SDL_GLContext context;

		private:
			void Initialise(SDL_Window* window);
			void Deinitialise();

		public:
			OpenGLRenderer(SDL_Window* window);
			~OpenGLRenderer();

			void SetViewport(GLuint width, GLuint height);

			void ClearColour(GLfloat red, GLfloat green, GLfloat blue);
			void Clear();

			void SwapBuffer(SDL_Window* window);
			void DrawTexture(const Texture& texture, const GLuint program, const GLuint VBO, const GLuint VAO, const GLuint EBO,
							 const Matrix4& model, const Matrix4& view, const Matrix4& perspective);
			
			Texture GenerateTexture(const SDL_Surface* surface);
			void DeleteTexture(Texture& texture);

			unsigned int GenerateVertexBufferObject(const std::vector<GLfloat>& vertices);
			unsigned int GenerateVertexArrayObject(const GLuint VBO);
			unsigned int GenerateElementBufferObject(const std::vector<GLushort>& indices);

			unsigned int GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

			void CheckErrors();
			GLint GetUniformLocation(const GLuint program, const char* name);
	};
}
