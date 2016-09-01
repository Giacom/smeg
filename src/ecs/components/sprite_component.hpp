#pragma once

#include "../component.hpp"

struct SpriteComponent: public Component {

	int x;
	int y;
	int w;
	int h;

	~SpriteComponent() {}
	SpriteComponent(int x, int y, int w, int h) : Component(), x(x), y(y), w(w), h(h) {}
};