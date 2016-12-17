#pragma once

#include "texture.hpp"
#include "math/vector3.hpp"

namespace smeg {
	struct SpriteBatch {
		Texture texture;
		int width;
		int height;
		Vector3 position;


		unsigned int shaderProgram;
		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;
		// TODO: Add Rect to draw
	};
}