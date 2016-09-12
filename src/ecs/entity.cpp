
#include <memory>
#include <typeinfo>
#include <typeindex>

#include "entity.hpp"
#include "component.hpp"


int Entity::autoComponentId = 0;

void Entity::AddComponent(std::unique_ptr<Component> &component) {
	component->id = ++autoComponentId;
	auto type = std::type_index(typeid(*component));
	components[type] = std::move(component);
 }