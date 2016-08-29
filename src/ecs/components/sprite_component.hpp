#pragma once

#include "../component.hpp"
#include "../component_type.hpp"

struct SpriteComponent: public Component {

	static ComponentType type;

	int x;
	int y;
	int w;
	int h;

	~SpriteComponent() {}
	SpriteComponent(int x, int y, int w, int h) : Component(), x(x), y(y), w(w), h(h) {}
};