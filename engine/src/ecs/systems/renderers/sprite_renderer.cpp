#include "SDL.h"
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
#include "io/file.hpp"

namespace smeg {

	SpriteRenderer::SpriteRenderer(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) :
	                               vertexShaderFilePath(vertexShaderFilePath), fragmentShaderFilePath(fragmentShaderFilePath) {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Sprite)));
		executionOrder = System::LATE;
	}

    void SpriteRenderer::Initialise(OpenGLRenderer &renderer) {
		std::string vertexShaderSource = File::LoadText(vertexShaderFilePath.c_str());
		std::string fragmentShaderSource = File::LoadText(fragmentShaderFilePath.c_str());

		shaderProgram = renderer.GenerateShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
    }

	void SpriteRenderer::Register(OpenGLRenderer &renderer, Entity &entity) {
		Sprite& sprite = entity.GetComponent<Sprite>();
		UpdateRenderData(renderer, sprite);
	}	
	
	void SpriteRenderer::Deregister(OpenGLRenderer &renderer, Entity &entity) {}

	void SpriteRenderer::Process(Entity &entity) {	}

	void SpriteRenderer::Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity) {
		Sprite& sprite = entity.GetComponent<Sprite>();
		Transform& transform = entity.GetComponent<Transform>();
		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();

		UpdateRenderData(renderer, sprite);

		auto texture = textureLibrary.LoadFile(renderer, sprite.GetTexturePath());
		batcher.Batch(texture, sprite.size, transform.position, sprite.indices.size(), shaderProgram, sprite.vbo, sprite.vao, sprite.ebo);
	}

	void SpriteRenderer::UpdateRenderData(OpenGLRenderer &renderer, Sprite &sprite) {
		if (!sprite.IsDirty()) {
			return;
		}

		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();
		
		auto texture = textureLibrary.LoadFile(renderer, sprite.GetTexturePath());
		Rect normalisedRect;
		if (sprite.GetDrawRect() == Rect()) {
			normalisedRect = Rect::New(0, 0, 1, 1);
		} else {
			normalisedRect = sprite.GetDrawRect().GetNormalisedRect(Vector2::New(texture.width, texture.height));
		}

		Vector2 topLeft = normalisedRect.TopLeft();
		Vector2 topRight = normalisedRect.TopRight();
		Vector2 bottomLeft = normalisedRect.BottomLeft();
		Vector2 bottomRight = normalisedRect.BottomRight();

		sprite.vertices = {
			// Positions          // Colors          // Texture Coords
			-0.5,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   topLeft.x, topLeft.y,
			-0.5f, -0.5f, 0.5f,  1.0f, 1.0f, 1.0f,   bottomLeft.x, bottomLeft.y,
			0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   bottomRight.x, bottomRight.y,
			0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   topRight.x, topRight.y
		};

		if (!sprite.vbo) {
			sprite.vbo = renderer.GenerateVertexBufferObject(sprite.vertices);
		} else {
			renderer.BindVertexBufferObject(sprite.vbo, sprite.vertices);
		}

		if (!sprite.vao) {
			sprite.vao = renderer.GenerateVertexArrayObject(sprite.vbo);
		}

		if (!sprite.ebo) {
			sprite.ebo = renderer.GenerateElementBufferObject(sprite.indices);
		}
	}
}