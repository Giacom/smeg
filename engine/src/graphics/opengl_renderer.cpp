#include "SDL.h"

#include "opengl_renderer.hpp"
#include "opengl.hpp"

namespace smeg {
	OpenGLRenderer::~OpenGLRenderer() {
		Deinitialise();
	}

	void OpenGLRenderer::Initialise(SDL_Window* window) {
		SDL_Log("Initialising OpenGLRenderer");
        
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		{
			i32 value = 0;
			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MAJOR_VERSION: %d\n", value);

			SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
			SDL_Log("SDL_GL_CONTEXT_MINOR_VERSION: %d\n", value);
		}

		context = SDL_GL_CreateContext(window);

		if (!context) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initialising GL Context: %s", SDL_GetError());
			throw;
		}

		OpenGL_Init();

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

	void OpenGLRenderer::DrawTexture(const Texture& texture, const u32 indiceCount, const ProgramID program, const VboID vbo, const VaoID vao, const EboID ebo,
	                                 const Matrix4& model, const Matrix4& view, const Matrix4& perspective) {
		if (!texture.id) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "DrawTexture: Invalid texture id (NULL)");
			throw;
		}

		glActiveTexture(GL_TEXTURE0);

		glUseProgram(program);
		glBindTexture(GL_TEXTURE_2D, texture.id);		

		glUniform1i(GetUniformLocation(program, "ourTexture"), 0);
		//glUniformMatrix4fv(GetUniformLocation(program, "model"), 1, GL_FALSE, (GLfloat*)&model.entries); 
		//glUniformMatrix4fv(GetUniformLocation(program, "view"), 1, GL_FALSE, (GLfloat*)&view.entries); 
		glUniformMatrix4fv(GetUniformLocation(program, "perspective"), 1, GL_FALSE, (GLfloat*)&perspective.entries); 

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

    Texture OpenGLRenderer::GenerateTexture(const SDL_Surface* image) {
        Texture texture;
        glGenTextures(1, &texture.id);
		
		if (!texture.id) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to convert texture from surface to texture!");
			CheckErrors();
			throw;
		}

		SDL_Log("Generating texture for %s", SDL_GetPixelFormatName(image->format->format));

		bool transparent = false;
		GLuint format = 0;

		switch (image->format->format) {
			case SDL_PIXELFORMAT_INDEX8:
				transparent = true;
				format = GL_RED;
				break;
			default:
				transparent = image->format->Amask != 0;
				format = transparent ? GL_RGBA : GL_RGB;
				break;
		}
		
		glBindTexture(GL_TEXTURE_2D, texture.id);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y wrapping

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Far away
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Close up

			glTexImage2D(GL_TEXTURE_2D, 0, transparent ? GL_RGBA : GL_RGB, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);
		}
		CheckErrors();
		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = image->w;
		texture.height = image->h;

		texture.flags |= (transparent ? TextureFlag::Transparent : TextureFlag::None); // Is transparent if there is alpha information
		SDL_Log("Generating texture: [id: %u, w: %u, h: %u, transparent: %s]",
		        texture.id, image->w, image->h, (texture.flags & TextureFlag::Transparent) ? "true" : "false");
        return texture;
    }
    
    void OpenGLRenderer::DeleteTexture(Texture& texture) {
        glDeleteTextures(1, &texture.id);
    }

	VboID OpenGLRenderer::GenerateVertexBufferObject(const GLfloat* vertices, const usize verticesLength) {
		GLuint VBO;
		glGenBuffers(1, &VBO);
		BindVertexBufferObject(VBO, vertices, verticesLength);
		SDL_Log("Generating vertex buffer: %u", VBO);
		return VBO;
	}

	void OpenGLRenderer::BindVertexBufferObject(const VboID VBO, const GLfloat* vertices, const usize verticesLength) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticesLength, vertices, GL_STREAM_DRAW);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	VboID OpenGLRenderer::GenerateVertexArrayObject(const VboID VBO) {
		GLuint VAO;
		glGenVertexArrays(1, &VAO);

		BindVertexArrayObject(VAO, VBO);
		SDL_Log("Generating vertex array: %u", VAO);

		return VAO;
	}

	void OpenGLRenderer::BindVertexArrayObject(const VaoID VAO, const VboID VBO) {
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
	}

	EboID OpenGLRenderer::GenerateElementBufferObject(const GLushort* indices, const usize indicesLength) {
		GLuint EBO;
		glGenBuffers(1, &EBO);
		BindElementBufferObject(EBO, indices, indicesLength);
		SDL_Log("Generating element buffer: %u", EBO);
		return EBO;
	}

	void OpenGLRenderer::BindElementBufferObject(const EboID EBO, const GLushort* indices, usize indicesLength) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indicesLength, indices, GL_STREAM_DRAW);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	ProgramID OpenGLRenderer::GenerateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
		GLint success;
		const u32 logBufferSize = 512;
		GLchar logBuffer[logBufferSize];

		// Vertex
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, logBufferSize, NULL, logBuffer);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Vertex Compile Error: %s", logBuffer);
			throw;
		}

		// Fragment
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, logBufferSize, NULL, logBuffer);
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Fragment Compile Error: %s", logBuffer);
			throw;
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
			throw;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	}

	void OpenGLRenderer::CheckErrors() {
		bool errorOccured = false;
		for(GLenum err; (err = glGetError()) != GL_NO_ERROR;) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Init: 0x%x", err);
			errorOccured = true;
		}
		if (errorOccured) {
			throw;
		}
	}

	UniformID OpenGLRenderer::GetUniformLocation(const ProgramID program, const char* name) {
		UniformID location = glGetUniformLocation(program, name);
		if (location == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not find shader's (%u) uniform location for: %s", program, name);
			throw;
		}
		return location;
	}
}
