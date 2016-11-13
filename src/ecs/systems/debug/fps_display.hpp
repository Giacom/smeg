#pragma once

#include "../../system.hpp"

namespace smeg {

    struct FpsDisplay: public System {
        FpsDisplay();
        void Process(Entity &entity);
    };
}