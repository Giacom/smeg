#pragma once

namespace smeg {

	struct Vector2 {
		float x, y; 

		Vector2() : x(0), y(0) {}
		Vector2(float x, float y) : x(x), y(y) {}

		static Vector2 Zero() {
			return Vector2(0, 0);
		}

		static Vector2 One() {
			return Vector2(1, 1);
		}

		Vector2 operator+(const Vector2& b) {
			return Vector2(this->x + b.x, this->y + b.y); 
		}

		Vector2 operator-(const Vector2& b) {
			return Vector2(this->x - b.x, this->y - b.y); 
		}

		Vector2 operator*(const float scale) {
			return Vector2(this->x * scale, this->y * scale);
		}
	};
}