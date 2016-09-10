#pragma once

#include "service.hpp"

struct Time: public Service {
    unsigned long current;
    unsigned long lastFrame;
    float delta;
};