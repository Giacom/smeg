#include "sprite.hpp"

namespace smeg {
	Sprite::Sprite(const std::string texturePath, int width, int height, int layer) :
		Component(), texturePath(texturePath), width(width), height(height), layer(layer) {}
}