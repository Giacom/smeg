#include "sprite.hpp"


Sprite::Sprite(const std::string texturePath, int w, int h) :
    Component(), texturePath(texturePath), w(w), h(h) {}