#pragma once

#include "SDL.h"
#include <vector>

#include "texture.hpp"
#include "opengl.hpp"
#include "math/matrix4.hpp"

namespace smeg {

	class OpenGLRenderer {
		private:
			SDL_GLContext context;


		public:
			~OpenGLRenderer();

			void Initialise(SDL_Window* window);
			void Deinitialise();
			
			void SetViewport(GLuint width, GLuint height);

			void ClearColour(GLfloat red, GLfloat green, GLfloat blue);
			void Clear();

			void SwapBuffer(SDL_Window* window);
			void DrawTexture(const Texture& texture, const u32 indiceCount, const GLuint program, const GLuint VBO, const GLuint VAO, const GLuint EBO,
							 const Matrix4& model, const Matrix4& view, const Matrix4& perspective);
			
			Texture GenerateTexture(const SDL_Surface* surface);
			void DeleteTexture(Texture& texture);

			u32 GenerateVertexBufferObject(const std::vector<GLfloat>& vertices);
			void BindVertexBufferObject(const GLuint VBO, const std::vector<GLfloat>& vertices);

			u32 GenerateVertexArrayObject(const GLuint VBO);
			void BindVertexArrayObject(const GLuint VAO, const GLuint VBO);

			u32 GenerateElementBufferObject(const std::vector<GLushort>& indices);
			void BindElementBufferObject(const GLuint EBO, const std::vector<GLushort>& indices);


			u32 GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

			void CheckErrors();
			GLint GetUniformLocation(const GLuint program, const char* name);
	};
}
