#pragma once

#include <vector>
#include "component.hpp"

struct Entity {
	std::vector<Component> components;

	Component GetComponent // TODO: How do we make this GetComponent<T>?
};