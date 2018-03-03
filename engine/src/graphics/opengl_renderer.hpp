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
			void DrawTexture(const Texture& texture, const u32 indiceCount, const ProgramID program, const VboID VBO, const VaoID VAO, const EboID EBO,
							 const Matrix4& model, const Matrix4& view, const Matrix4& perspective);
			
			Texture GenerateTexture(const SDL_Surface* surface);
			void DeleteTexture(Texture& texture);

			VboID GenerateVertexBufferObject(const GLfloat* vertices, const usize verticesLength);
			void BindVertexBufferObject(const VboID VBO, const GLfloat* vertices, const usize verticesLength);

			VaoID GenerateVertexArrayObject(const VboID VBO);
			void BindVertexArrayObject(const VaoID VAO, const VboID VBO);

			EboID GenerateElementBufferObject(const GLushort* indices, usize indicesLength);
			void BindElementBufferObject(const EboID EBO, const GLushort* indices, usize indicesLength);


			ProgramID GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

			void CheckErrors();
			UniformID GetUniformLocation(const ProgramID program, const char* name);
	};
}
