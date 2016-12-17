#include <SDL2/SDL.h>
#include <memory>

#include "sprite_renderer.hpp"
#include "graphics/opengl_renderer.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/components/sprite.hpp"
#include "ecs/components/transform.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"
#include "service/viewport.hpp"

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
	}

	void SpriteRenderer::Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity) {
		Sprite& sprite = entity.GetComponent<Sprite>();
		Transform& transform = entity.GetComponent<Transform>();

		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();

		auto texture = textureLibrary.LoadFile(renderer, sprite.texturePath);
		batcher.Batch(texture, sprite.width, sprite.height, transform.position, shaderProgram, vbo, vao, ebo);
	}
}