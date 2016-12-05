#include <SDL.h>

#include "opengl_renderer.hpp"
#include "opengl.hpp"

namespace smeg {
	void OpenGLRenderer::Initialise(SDL_Window* window) {
		context = SDL_GL_CreateContext(window);

		if (!context) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising GL Context: %s", SDL_GetError());
		}
        
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		{
			int value = 0;
			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MAJOR_VERSION: %d\n", value);

			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MINOR_VERSION: %d\n", value);
		}

        OpenGL_Init();
	}

	void OpenGLRenderer::Deinitialise() {
		SDL_GL_DeleteContext(context);
	}

	void OpenGLRenderer::ClearColour(float red, float green, float blue) {
		glClearColor(red, green, blue, 1.0f);
	}    

	void OpenGLRenderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

    void OpenGLRenderer::SwapBuffer(SDL_Window* window) {
        SDL_GL_SwapWindow(window);
    }

    Texture OpenGLRenderer::GenTexture() {
        Texture texture;
        glGenTextures(1, &texture.id);
        return texture;
    }

    void OpenGLRenderer::DeleteTexture(Texture& texture) {
        glDeleteTextures(1, &texture.id);
    }
}
