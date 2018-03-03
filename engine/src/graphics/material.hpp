#pragma once

#include "common.hpp"
#include "texture.hpp"

namespace smeg {

	struct Material {
		Texture texture;
		u32 program;
	};
}