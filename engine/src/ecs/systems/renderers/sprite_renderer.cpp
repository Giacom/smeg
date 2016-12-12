#include <SDL2/SDL.h>
#include <memory>

#include "sprite_renderer.hpp"
#include "../../../graphics/opengl_renderer.hpp"
#include "../../system.hpp"
#include "../../entity.hpp"
#include "../../components/sprite.hpp"
#include "../../components/transform.hpp"
#include "../../../service/texture_library.hpp"
#include "../../../service/time.hpp"

namespace smeg {

	SpriteRenderer::SpriteRenderer() {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Sprite)));
		executionOrder = System::LATE;
	}

    void SpriteRenderer::Initialise(OpenGLRenderer &renderer) {
		vbo = renderer.GenerateVertexBufferObject(vertices);
		vao = renderer.GenerateVertexArrayObject(vbo);
		ebo = renderer.GenerateElementBufferObject(indices);
		shaderProgram = renderer.GenerateShaderProgram(defaultVertexShaderSource, defaultFragmentShaderSource);
    }

	void SpriteRenderer::Process(Entity &entity) {
		/*
		Transform& transform = entity.GetComponent<Transform>();
		Time& time = serviceContainer->Get<Time>();

		transform.position.x += (100.0f * time.delta);
		if (transform.position.x > 500) {
			transform.position.x = -100;
		}
		*/
	}

	void SpriteRenderer::Render(OpenGLRenderer &renderer, Entity &entity) {
		Sprite& sprite = entity.GetComponent<Sprite>();

		Transform& transform = entity.GetComponent<Transform>();
		Matrix4 matrixTransform = Matrix4(1, 0, 0, 0,
		                                  0, 1, 0, 0,
										  0, 0, 1, 0,
										  transform.position.x, transform.position.y, transform.position.z, 1);

		auto& textureLibrary = serviceContainer->Get<TextureLibrary>();
		auto texture = textureLibrary.LoadFile(renderer, sprite.texturePath);

		renderer.DrawTexture(texture, shaderProgram, vbo, vao, ebo, matrixTransform);
	}
}