#pragma once

#include "../component.hpp"
#include "../../math/vector2.hpp"

struct Transform: public Component {
    Vector2 position;

    Transform(float x, float y) {
        Vector2 position(x, y);
        this->position = position;
    }

    Transform(Vector2 position) : position(position) {}
};