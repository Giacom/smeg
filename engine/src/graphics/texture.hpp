#pragma once

#include "common.hpp"

namespace smeg {

	using TextureFlags = u32;
	namespace TextureFlag {
		enum {
			None = 0,
			Transparent = 1 << 0,
			Unused = 1 << 1
		};
	}

	struct Texture {
		u32 id;
		u32 width;
		u32 height;
		TextureFlags flags;
	};
}