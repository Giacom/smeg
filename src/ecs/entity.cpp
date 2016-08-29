
#include "entity.hpp"
#include "component.hpp"
#include "component_type.hpp"

#include <memory>

void Entity::AddComponent(std::unique_ptr<Component> &component) {
	components.push_back(std::move(component));
}

Component* Entity::GetBaseComponent(ComponentType type) {
	for(auto &component : components) {
		if (component->type == type) {
			return component.get();
		}
	}
	return nullptr;
}