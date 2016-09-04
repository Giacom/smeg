#pragma once

#include <string>
#include "../component.hpp"

struct Sprite: public Component {

	std::string texturePath;

	int x;
	int y;
	int w;
	int h;

	~Sprite() {}
	Sprite(const std::string texturePath, int x, int y, int w, int h);
};