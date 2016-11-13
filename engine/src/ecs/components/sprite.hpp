#pragma once

#include <string>
#include "../component.hpp"

namespace smeg {

	struct Sprite: public Component {

		std::string texturePath;
		
		int w;
		int h;
		int layer;

		~Sprite() {}
		Sprite(const std::string texturePath, int w, int h, int layer = 0);
	};
}