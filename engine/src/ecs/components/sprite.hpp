#pragma once

#include <string>
#include "../component.hpp"

namespace smeg {

	struct Sprite: public Component {

		std::string texturePath;
		
		int width;
		int height;
		int layer;
        

		Sprite(const std::string texturePath, int width, int height, int layer = 0);
	};
}