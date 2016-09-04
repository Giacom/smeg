#include "sprite.hpp"


Sprite::Sprite(const std::string texturePath, int x, int y, int w, int h) :
    Component(), texturePath(texturePath), x(x), y(y), w(w), h(h) {}