#pragma once

#include "math/vector2.hpp"

namespace smeg {
	/// Meta-data about each character glyph and its size metrics
	struct Character {
		Vector2 size;
		Vector2 bearing;
		float advance;
	};
}