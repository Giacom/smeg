#pragma once

namespace smeg {

	struct Vector3 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		Vector3() = default;
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		static Vector3 Zero() {
			return Vector3(0, 0, 0);
		}

		static Vector3 One() {
			return Vector3(1, 1, 1);
		}

		Vector3 operator+(const Vector3& b) const {
			return Vector3(this->x + b.x, this->y + b.y, this->z + b.z); 
		}

		Vector3 operator-(const Vector3& b) const {
			return Vector3(this->x - b.x, this->y - b.y, this->z - b.z); 
		}

		Vector3 operator*(const float scale) const {
			return Vector3(this->x * scale, this->y * scale, this->z * scale);
		}

		bool operator==(const Vector3& b) const {
			return this->x == b.x && this->y == b.y && this->z == b.z;
		}
	};
}