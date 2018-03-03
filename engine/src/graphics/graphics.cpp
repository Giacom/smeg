#include "graphics.hpp"

namespace smeg {

	void Graphics::Initialise(OpenGLRenderer* renderer, Viewport* viewport) {
		this->renderer = renderer;
		this->viewport = viewport;
		defaultProgram = renderer->GenerateShaderProgram(defaultShaderVert, defaultShaderFrag);
		activeProgram = defaultProgram;

		f32 vertices[verticesLength] = { 0.0f };
		u16 indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		usize indicesLength = ARRAY_LENGTH(indices);

		vbo = renderer->GenerateVertexBufferObject(vertices, verticesLength);
		vao = renderer->GenerateVertexArrayObject(vbo);
		ebo = renderer->GenerateElementBufferObject(indices, indicesLength);
	}

	void Graphics::SetActiveProgram(ProgramID program) {
		activeProgram = program > 0 ? program : defaultProgram;
	}

	void Graphics::DrawTexture(const Texture& texture, Vector2 position) {
		f32 vertices[] = {
			position.x, position.y, 0,	/* */ 1.0, 1.0, 1.0, /* */ 0.0, 0.0, 
			position.x, position.y + texture.height, 0, /* */ 1.0, 1.0, 1.0, /* */ 0.0, 1.0,
			position.x + texture.width, position.y + texture.height, 0, /* */ 1.0, 1.0, 1.0, /* */ 1.0, 1.0,
			position.x + texture.width, position.y, 0, /* */ 1.0, 1.0, 1.0, /* */ 1.0, 0.0,
		};

		renderer->BindVertexBufferObject(vbo, vertices, verticesLength);
		renderer->DrawTexture(texture, 6, activeProgram, vbo, vao, ebo, Matrix4::Identity(), Matrix4::Identity(), viewport->GetPerspectiveMatrix());
	}

	Texture Graphics::LoadTexture(const SDL_Surface* image) {
		return renderer->GenerateTexture(image);
	}
}