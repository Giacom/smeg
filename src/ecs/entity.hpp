#pragma once

#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include "component.hpp"

struct Entity {
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

	void AddComponent(std::unique_ptr<Component> &component);

	template<typename T>
	T& GetComponent() {
		return *dynamic_cast<T*>(components.at(std::type_index(typeid(T))).get());
	}
};