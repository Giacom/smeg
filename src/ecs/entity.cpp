
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <iostream>

#include "entity.hpp"
#include "component.hpp"
#include "components/sprite_component.hpp"
#include "components/text_component.hpp"


void Entity::AddComponent(std::unique_ptr<Component> &component) {
	auto type = std::type_index(typeid(*component));
	components[type] = std::move(component);
 }