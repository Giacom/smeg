#pragma once

namespace smeg {

	struct Vector3 {
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		static Vector3 New() {
			return Vector3();
		}

		static Vector3 New(float x, float y, float z) {
			return Vector3 { x, y, z };
		}

		static Vector3 Zero() {
			return Vector3::New(0, 0, 0);
		}

		static Vector3 One() {
			return Vector3::New(1, 1, 1);
		}

		Vector3 operator+(const Vector3& b) const {
			return Vector3::New(this->x + b.x, this->y + b.y, this->z + b.z); 
		}

		Vector3 operator-(const Vector3& b) const {
			return Vector3::New(this->x - b.x, this->y - b.y, this->z - b.z);
		}

		Vector3 operator*(const float scale) const {
			return Vector3::New(this->x * scale, this->y * scale, this->z * scale);
		}

		bool operator==(const Vector3& b) const {
			return this->x == b.x && this->y == b.y && this->z == b.z;
		}
	};
}