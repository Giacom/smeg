#pragma once

#include <vector>
#include <memory>
#include "component_type.hpp"
#include "component.hpp"

struct Entity {
	std::vector<std::unique_ptr<Component>> components;

	void AddComponent(std::unique_ptr<Component> &component);

	template<typename T>
	T* GetComponent() {
			return dynamic_cast<T*>(GetBaseComponent(T::type));
	}

	Component* GetBaseComponent(ComponentType type);
};