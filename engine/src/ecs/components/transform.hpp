#pragma once

#include "ecs/component.hpp"
#include "math/vector3.hpp"

namespace smeg {
	struct Transform: public Component {
		Vector3 position;
		f32 rotation;

		Transform(f32 x, f32 y, f32 z, f32 rotation) {
			Vector3 position = Vector3::New(x, y, z);
			this->position = position;
			this->rotation = rotation;
		}

		Transform(Vector3 position, f32 rotation) : position(position), rotation(rotation) {}
	};
}