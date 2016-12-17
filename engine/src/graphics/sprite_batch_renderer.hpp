#pragma once

#include "sprite_batch.hpp"
#include "opengl_renderer.hpp"

#include <vector>

namespace smeg {
	class SpriteBatchRenderer {
		std::vector<SpriteBatch> opaqueBatches;
		std::vector<SpriteBatch> transparentBatches;

		public:
			void Start();
			void Batch(Texture texture, int width, int height, Vector3 position,
			           unsigned int shaderProgram, unsigned int vbo, unsigned int vao, unsigned int ebo);
			void Render(OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective);
	};
}