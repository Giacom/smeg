#pragma once

#include <string>
#include "ecs/component.hpp"

namespace smeg {

	struct Sprite: public Component {

		std::string texturePath;
		
		int width;
		int height;

		Sprite(const std::string texturePath, int width, int height) :
		       Component(), texturePath(texturePath), width(width), height(height) {}
	};
}