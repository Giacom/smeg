#pragma once

#include "vector2.hpp"

namespace smeg {
	/// Rectangles that start at the top left and expand to the bottom right
	struct Rect {
		Vector2 origin;
		Vector2 size;

		static Rect New() {
			return Rect();
		}

		static Rect New(float x, float y, float width, float height) {
			return Rect { Vector2 { x, y }, Vector2 { width, height} };
		}

		static Rect New(Vector2 origin, Vector2 size) {
			return Rect { origin, size };
		}

		/// Give two coordinates and it will calculate the width and height of the Rect
		static Rect PointToPoint(float x0, float y0, float x1, float y1) {
			return Rect { Vector2 { x0, y0 }, Vector2 { x1 - x0, y1 - y0 } };
		}

		Vector2 TopLeft() const {
			return origin;
		}
		
		Vector2 TopRight() const {
			return Vector2::New(origin.x + size.x, origin.y);
		}

		Vector2 BottomLeft() const {
			return Vector2::New(origin.x, origin.y + size.y);
		}

		Vector2 BottomRight() const {
			return origin + size;
		}

		bool operator==(const Rect& b) const {
			return this->origin == b.origin && this->size == b.size;
		}

		Rect GetNormalisedRect(Vector2 normalisedFrom) const {
			Vector2 normalisedOrigin = Vector2::New(origin.x / normalisedFrom.x, origin.y / normalisedFrom.y);
			Vector2 normalisedSize = Vector2::New(size.x / normalisedFrom.x, size.y / normalisedFrom.y);
			return Rect::New(normalisedOrigin, normalisedSize);
		}
	};
}