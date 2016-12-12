#pragma once

namespace smeg {

	struct Vector3 {
		float x, y, z; 

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		static Vector3 Zero() {
			return Vector3(0, 0, 0);
		}

		static Vector3 One() {
			return Vector3(1, 1, 1);
		}

		Vector3 operator+(const Vector3& b) {
			return Vector3(this->x + b.x, this->y + b.y, this->z + b.z); 
		}

		Vector3 operator-(const Vector3& b) {
			return Vector3(this->x - b.x, this->y - b.y, this->z - b.z); 
		}

		Vector3 operator*(const float scale) {
			return Vector3(this->x * scale, this->y * scale, this->z * scale);
		}
	};
}