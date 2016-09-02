#pragma once

#include "../component.hpp"

struct Sprite: public Component {

	int x;
	int y;
	int w;
	int h;

	~Sprite() {}
	Sprite(int x, int y, int w, int h) : Component(), x(x), y(y), w(w), h(h) {}
};