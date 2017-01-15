#pragma once

#include <string>
#include <unordered_map>

#include "character.hpp"

/*
	TODO:
		Draw a simple bitmap font first
		Figure out how to draw different characters with one draw

*/

namespace smeg {
	struct Font {
		std::string textureFontId;
		std::unordered_map<char, Character> characters;
		float pixelSize;
	};
}