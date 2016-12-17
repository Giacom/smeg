#pragma once

#include "ecs/component.hpp"
#include "math/vector3.hpp"

namespace smeg {
	struct Transform: public Component {
		Vector3 position;
		float rotation;

		Transform(float x, float y, float z, float rotation) {
			Vector3 position(x, y, z);
			this->position = position;
			this->rotation = rotation;
		}

		Transform(Vector3 position, float rotation) : position(position), rotation(rotation) {}
	};
}