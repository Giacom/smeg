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

		Rect(Vector2 origin, Vector2 size) : origin(origin), size(size) {}

		Vector2 TopLeft() const {
			return origin;
		}
		
		Vector2 TopRight() const {
			return Vector2(origin.x + size.x, origin.y);
		}

		Vector2 BottomLeft() const {
			return Vector2(origin.x, origin.y + size.y);
		}

		Vector2 BottomRight() const {
			return origin + size;
		}

		bool operator==(const Rect& b) const {
			return this->origin == b.origin && this->size == b.size;
		}

		Rect GetNormalisedRect(Vector2 normalisedFrom) const {
			Vector2 normalisedOrigin = Vector2(origin.x / normalisedFrom.x, origin.y / normalisedFrom.y);
			Vector2 normalisedSize = Vector2(size.x / normalisedFrom.x, size.y / normalisedFrom.y);
			return Rect(normalisedOrigin, normalisedSize);
		}
	};
}