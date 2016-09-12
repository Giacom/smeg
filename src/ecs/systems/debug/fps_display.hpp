#pragma once

#include "../../system.hpp"

struct FpsDisplay: public System {
    FpsDisplay();
    void Process(Entity &entity);
};