#include "sprite_batch_renderer.hpp"

#include <algorithm>

namespace smeg {
	void SpriteBatchRenderer::Start() {
		transparentBatches.clear();
		opaqueBatches.clear();
	}

	void SpriteBatchRenderer::Batch(Texture texture, int width, int height, Vector3 position,
	                                unsigned int shaderProgram, unsigned int vbo,unsigned int vao, unsigned int ebo) {
		SpriteBatch spriteBatch = { texture, width, height, position, shaderProgram, vbo, vao, ebo };

		if (spriteBatch.texture.transparent) {
			// Sort the order if the texture is transparent
			transparentBatches.emplace_back(spriteBatch);
			
			std::sort(transparentBatches.begin(), transparentBatches.end(), [](const SpriteBatch &lhs, const SpriteBatch &rhs) {
				return lhs.position.z < rhs.position.z;
			});

		} else {
			opaqueBatches.emplace_back(spriteBatch);
		}
	}

	void SpriteBatchRenderer::Render(OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective) {
		auto renderOperation = [](OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective, const SpriteBatch& batch) {
			const Matrix4 model = Matrix4(batch.width,   0,              0,         batch.position.x,
										  0,             batch.height,   0,         batch.position.y,
										  0,             0,              1,         batch.position.z,
										  0,             0,              0,         1);
			renderer.DrawTexture(batch.texture, batch.shaderProgram, batch.vbo, batch.vao, batch.ebo, model, view, perspective);
		};

		for (auto& batch : opaqueBatches) {
			renderOperation(renderer, view, perspective, batch);
		}

		for (auto& batch : transparentBatches) {
			renderOperation(renderer, view, perspective, batch);
		}
	}
}