#pragma once

#include "texture.hpp"

namespace smeg {
	enum class RenderLayer {
		Opaque,
		Transparent,
		Overlay
	};

	struct RenderCommand {
		Texture texture;
	};
}