#include "sprite.hpp"

namespace smeg {
	Sprite::Sprite(const std::string texturePath, int w, int h, int layer) :
		Component(), texturePath(texturePath), w(w), h(h), layer(layer) {}
}