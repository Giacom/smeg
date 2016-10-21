#pragma once

#include "service.hpp"

struct Time: public Service {
    static constexpr float MS_TO_SEC = 0.001f;
    static constexpr float SEC_TO_MS = 1000.0f;

    long ticks;
    int fps;

    int targetFrameRate = 60;

    double current;
    double lastFrame;
    double delta;
};