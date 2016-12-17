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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderer::Deinitialise() {
		SDL_GL_DeleteContext(context);
	}

	void OpenGLRenderer::SetViewport(GLuint width, GLuint height) {
		glViewport(0, 0, width, height);
	}

	void OpenGLRenderer::ClearColour(GLfloat red, GLfloat green, GLfloat blue) {
		glClearColor(red, green, blue, 1.0f);
	}    

	void OpenGLRenderer::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void OpenGLRenderer::SwapBuffer(SDL_Window* window) {
        SDL_GL_SwapWindow(window);
    }

	void OpenGLRenderer::DrawTexture(const Texture& texture, const GLuint program, const GLuint vbo, const GLuint vao, const GLuint ebo,
	                                 const Matrix4& model, const Matrix4& view, const Matrix4& perspective) {
		if (!texture.id) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "DrawTexture: Invalid texture id (NULL)");
		}

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(program);
		glBindTexture(GL_TEXTURE_2D, texture.id);		

		glUniform1i(GetUniformLocation(program, "ourTexture"), 0);
		glUniformMatrix4fv(GetUniformLocation(program, "model"), 1, GL_FALSE, (GLfloat*)&model.entries); 
		glUniformMatrix4fv(GetUniformLocation(program, "view"), 1, GL_FALSE, (GLfloat*)&view.entries); 
		glUniformMatrix4fv(GetUniformLocation(program, "perspective"), 1, GL_FALSE, (GLfloat*)&perspective.entries); 

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

    Texture OpenGLRenderer::GenerateTexture(const SDL_Surface* image) {
        Texture texture;
		SDL_Log("Generating texture for %s", SDL_GetPixelFormatName(image->format->format));
        glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y wrapping

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Far away
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Close up

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = image->w;
		texture.height = image->h;
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

	unsigned int OpenGLRenderer::GenerateVertexArrayObject(const GLuint VBO) {
		GLuint VAO;
		glGenVertexArrays(1, &VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return VAO;
	}

	unsigned int OpenGLRenderer::GenerateElementBufferObject(const std::vector<GLushort>& indices) {
		GLuint EBO;
		glGenBuffers(1, &EBO);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), indices.data(), GL_STATIC_DRAW);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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

	void OpenGLRenderer::CheckErrors() {
		for(GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Init: 0x%x", err);
		}
	}

	GLint OpenGLRenderer::GetUniformLocation(const GLuint program, const char* name) {
		GLint location = glGetUniformLocation(program, name);
		if (location == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not find shader's (%u) uniform location for: %s", program, name);
		}
		return location;
	}
}
