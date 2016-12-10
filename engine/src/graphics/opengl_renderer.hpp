#pragma once

#include <SDL.h>
#include <vector>

#include "texture.hpp"
#include "opengl.hpp"

namespace smeg {

	class OpenGLRenderer {
        private:
	        SDL_GLContext context;

        public:
            OpenGLRenderer(SDL_Window* window);
            ~OpenGLRenderer();

            void ClearColour(float red, float green, float blue);
            void Clear();

            void SwapBuffer(SDL_Window* window);
            
			Texture GenTexture();
			void DeleteTexture(Texture& texture);

            unsigned int GenerateVertexBufferObject(const std::vector<GLfloat>& vertices);
            unsigned int GenerateVertexArrayObject();
            unsigned int GenerateElementBufferObject(const std::vector<GLuint>& indices);

            unsigned int GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);


        private:
            void Initialise(SDL_Window* window);
            void Deinitialise();

	};
}
