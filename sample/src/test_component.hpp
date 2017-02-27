#pragma once

#include "ecs/component.hpp"

struct TestComponent : public smeg::Component {
	int duckIndex = 0;
	int duckShown = 0;

	TestComponent(int duckIndex, int duckShown) : duckIndex(duckIndex), duckShown(duckShown) {};
};