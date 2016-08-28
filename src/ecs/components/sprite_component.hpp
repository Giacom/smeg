#pragma once

#include "../component.hpp"

struct SpriteComponent: public Component {
	int x;
	int y;
	int width;
	int height;

	SpriteComponent(int x, int y, int width, int height) : Component(), x(x), y(y), width(width), height(height) {
		type = 1;
	}
};