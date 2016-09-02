
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <iostream>

#include "entity.hpp"
#include "component.hpp"


void Entity::AddComponent(std::unique_ptr<Component> &component) {
	auto type = std::type_index(typeid(*component));
	components[type] = std::move(component);
 }