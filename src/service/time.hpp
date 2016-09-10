#pragma once

#include "service.hpp"

struct Time: public Service {
    static constexpr float MS_TO_SEC = 0.001f;

    unsigned long current;
    unsigned long lastFrame;
    float delta;
};