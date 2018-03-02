#include "sprite_batch_renderer.hpp"

#include <algorithm>

namespace smeg {
	void SpriteBatchRenderer::Start() {
		transparentBatches.clear();
		opaqueBatches.clear();
	}

	void SpriteBatchRenderer::Batch(const Texture& texture, const Vector2& size, const Vector3& position,
	                                const unsigned int indiceCount, const unsigned int shaderProgram, const unsigned int vbo, const unsigned int vao, const unsigned int ebo) {
		SpriteBatch spriteBatch = { texture, size, position, indiceCount, shaderProgram, vbo, vao, ebo };

		if (spriteBatch.texture.flags & TEXTURE_FLAG_TRANSPARENT) {
			// Sort the order if the texture is transparent
			transparentBatches.push_back(spriteBatch);
			
			std::sort(transparentBatches.begin(), transparentBatches.end(), [](const SpriteBatch &lhs, const SpriteBatch &rhs) {
				return lhs.position.z < rhs.position.z;
			});

		} else {
			opaqueBatches.push_back(spriteBatch);
		}
	}

	void SpriteBatchRenderer::Render(OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective) {
		auto renderOperation = [](OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective, const SpriteBatch& batch) {
			const Matrix4 model = Matrix4::New(batch.size.x,   0,                   0,         batch.position.x,
										       0,              batch.size.y,        0,         batch.position.y,
										       0,              0,                   1,         batch.position.z,
										       0,              0,                   0,         1);
			renderer.DrawTexture(batch.texture, batch.indiceCount, batch.shaderProgram, batch.vbo, batch.vao, batch.ebo, model, view, perspective);
		};

		for (auto& batch : opaqueBatches) {
			renderOperation(renderer, view, perspective, batch);
		}

		for (auto& batch : transparentBatches) {
			renderOperation(renderer, view, perspective, batch);
		}
	}
}