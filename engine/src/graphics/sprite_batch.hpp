#pragma once

#include "texture.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"

namespace smeg {
	struct SpriteBatch {
		Texture texture;

		Vector2 size;
		Vector3 position;

		u32 indiceCount;

		u32 shaderProgram;
		u32 vbo;
		u32 vao;
		u32 ebo;
	};
}