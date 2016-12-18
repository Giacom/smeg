#pragma once

#include <string>
#include "ecs/component.hpp"
#include "math/rect.hpp"
#include "math/vector2.hpp"

namespace smeg {

	struct Sprite: public Component {

		const std::string texturePath;
		const Rect drawRect;
		const Vector2 size;

		unsigned int vbo;
		unsigned int vao;
		unsigned int ebo;

		std::vector<float> vertices;

		const std::vector<unsigned short> indices = {
			0, 1, 2,
			2, 3, 0,
		};

		Sprite(const std::string texturePath, Rect drawRect, Vector2 size) :
			   Component(), texturePath(texturePath), drawRect(drawRect), size(size) {}
	};
}