#pragma once

#include "vector2.hpp"

namespace smeg {
	/// Rectangles that start at the top left and expand to the bottom right
	struct Rect {
		Vector2 origin;
		Vector2 size;

		Rect() = default;

		Rect(float x, float y, float width, float height) {
			origin = Vector2(x, y);
			size = Vector2(width, height);
		}		
	};
}