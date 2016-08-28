#pragma once

#include "component_type.hpp"

struct Component {
	virtual ~Component() {};
	ComponentType type;
};