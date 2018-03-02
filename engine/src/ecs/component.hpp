#pragma once

#include "common.hpp"

namespace smeg {

	struct Component {
		u32 id;
		virtual ~Component() {};
	};
}