#pragma once

#include <vector>
#include <memory>
#include "component_type.hpp"
#include "component.hpp"

struct Entity {
	std::vector<std::unique_ptr<Component>> components;

	void AddComponent(std::unique_ptr<Component> &component);
	Component* GetComponent(ComponentType type);
};