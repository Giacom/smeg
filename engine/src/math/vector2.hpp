#pragma once

#include "common.hpp"

namespace smeg {

	struct Vector2 {
		f32 x = 0.0f;
		f32 y = 0.0f;

		static Vector2 New() {
			return Vector2();
		}

		static Vector2 New(f32 x, f32 y) {
			return Vector2{ x, y };
		}

		static Vector2 Zero() {
			return Vector2::New(0, 0);
		}

		static Vector2 One() {
			return Vector2::New(1, 1);
		}

		Vector2 operator+(const Vector2& b) const {
			return Vector2::New(this->x + b.x, this->y + b.y); 
		}

		Vector2 operator-(const Vector2& b) const {
			return Vector2::New(this->x - b.x, this->y - b.y); 
		}

		Vector2 operator*(const f32 scale) const {
			return Vector2::New(this->x * scale, this->y * scale);
		}

		bool operator==(const Vector2& b) const {
			return this->x == b.x && this->y == b.y;
		}
	};
}