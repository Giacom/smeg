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
			void Batch(const Texture& texture, const Vector2& size, const Vector3& position,
			           const u32 indiceCount, const u32 shaderProgram, const u32 vbo, const u32 vao, const u32 ebo);
			void Render(OpenGLRenderer& renderer, const Matrix4& view, const Matrix4& perspective);
	};
}