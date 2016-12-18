#pragma once

#include <string>
#include "ecs/component.hpp"
#include "math/rect.hpp"
#include "math/vector2.hpp"

namespace smeg {

	struct Sprite: public Component {

		std::string texturePath;
		Rect textureRect;
		Vector2 size;

		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;

		const std::vector<float> vertices = { 
			// Positions          // Colors           	  // Texture Coords
			-0.5,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,  // Top Left 
			-0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Bottom Left
			0.5f, -0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
			0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top Right
		};

		const std::vector<unsigned short> indices = {
			0, 1, 2,
			2, 3, 0,
		};

		Sprite(const std::string texturePath, Rect textureRect, Vector2 size) :
			   Component(), texturePath(texturePath), textureRect(textureRect), size(size) {}
	};
}