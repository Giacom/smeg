#pragma once

namespace smeg {

	struct Vector2 {
		float x = 0.0f;
		float y = 0.0f; 

		Vector2() = default;
		Vector2(float x, float y) : x(x), y(y) {}

		static Vector2 Zero() {
			return Vector2(0, 0);
		}

		static Vector2 One() {
			return Vector2(1, 1);
		}

		Vector2 operator+(const Vector2& b) const {
			return Vector2(this->x + b.x, this->y + b.y); 
		}

		Vector2 operator-(const Vector2& b) const {
			return Vector2(this->x - b.x, this->y - b.y); 
		}

		Vector2 operator*(const float scale) const {
			return Vector2(this->x * scale, this->y * scale);
		}

		bool operator==(const Vector2& b) const {
			return this->x == b.x && this->y == b.y;
		}
	};
}