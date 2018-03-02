#pragma once

#include "common.hpp"
#include "service.hpp"

namespace smeg {
	
	struct Time: public Service {
		static constexpr f64 MS_TO_SEC = 0.001f;
		static constexpr f64 SEC_TO_MS = 1000.0f;

		u64 ticks;
		f64 fps;

		i32 targetFrameRate = 60;

		f64 current;
		f64 lastFrame;
		f64 delta;
	};
}