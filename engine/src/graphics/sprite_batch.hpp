#pragma once

#include "texture.hpp"
#include "math/vector2.hpp"
#include "math/vector3.hpp"

namespace smeg {
	struct SpriteBatch {
		Texture texture;

		Vector2 size;
		Vector3 position;

		unsigned int shaderProgram;
		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;
	};
}