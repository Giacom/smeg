#include <SDL.h>

#include "opengl_renderer.hpp"
#include "opengl.hpp"

namespace smeg {
	OpenGLRenderer::OpenGLRenderer(SDL_Window* window) {
		Initialise(window);
	}

	OpenGLRenderer::~OpenGLRenderer() {
		Deinitialise();
	}

	void OpenGLRenderer::Initialise(SDL_Window* window) {
		SDL_Log("Initialising OpenGLRenderer");
        
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        OpenGL_Init();

		{
			int value = 0;
			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MAJOR_VERSION: %d\n", value);

			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MINOR_VERSION: %d\n", value);
		}

		context = SDL_GL_CreateContext(window);

		if (!context) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising GL Context: %s", SDL_GetError());
		}
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

	unsigned int OpenGLRenderer::GenerateVertexBufferObject(const std::vector<GLfloat>& vertices) {
		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return VBO;
	}

	unsigned int OpenGLRenderer::GenerateVertexArrayObject() {
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		{
			// Position
			glVertexAttribPointer(0, // Layout
								3, // Size
								GL_FLOAT, // Type
								GL_FALSE, // Normalised
								8 * sizeof(GLfloat), // Stride
								(void*) 0); // Array Buffer Offset
			glEnableVertexAttribArray(0);

			// Colour
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);

			// Tex Coord
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
		glBindVertexArray(0);
		return VAO;
	}

	unsigned int OpenGLRenderer::GenerateElementBufferObject(const std::vector<GLuint>& indices) {
		GLuint EBO;
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		return EBO;
	}
	
	unsigned int OpenGLRenderer::GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
		GLint success;
		const unsigned int logBufferSize = 512;
		GLchar logBuffer[logBufferSize];

		// Vertex
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, logBufferSize, NULL, logBuffer);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Vertex Compile Error: %s", logBuffer);
		}

		// Fragment
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, logBufferSize, NULL, logBuffer);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Fragment Compile Error: %s", logBuffer);
		}

		// Program
		GLuint shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, logBufferSize, NULL, logBuffer);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader Linking Error: %s", logBuffer);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	}
}
