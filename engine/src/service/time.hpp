#pragma once

#include "common.hpp"
#include "service.hpp"

namespace smeg {
	
	struct Time: public Service {
		static constexpr double MS_TO_SEC = 0.001f;
		static constexpr double SEC_TO_MS = 1000.0f;

		u64 ticks;
		double fps;

		i32 targetFrameRate = 60;

		double current;
		double lastFrame;
		double delta;
	};
}