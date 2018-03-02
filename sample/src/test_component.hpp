#pragma once

#include "ecs/component.hpp"

struct TestComponent : public smeg::Component {
	i32 duckIndex = 0;
	i32 duckShown = 0;

	TestComponent(i32 duckIndex, i32 duckShown) : duckIndex(duckIndex), duckShown(duckShown) {};
};