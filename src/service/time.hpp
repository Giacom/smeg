#pragma once

#include "service.hpp"

struct Time: public Service {
    static constexpr float MS_TO_SEC = 0.001f;

    long ticks;

    double current;
    double lastFrame;
    double fps;
    double delta;
};