#pragma once

#include "common.hpp"

const u32 TEXTURE_FLAG_NONE = 0;
const u32 TEXTURE_FLAG_TRANSPARENT = 1 << 0;
const u32 TEXTURE_FLAG_UNUSED = 1 << 1;

namespace smeg {

	struct Texture {
		u32 id;
		u32 width;
		u32 height;
		u32 flags;
	};
}