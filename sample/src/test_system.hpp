#pragma once

#include "ecs/system.hpp"

struct TestSystem : public smeg::System {
	TestSystem();

	void Initialise();

	void Register(smeg::Entity& entity);
	void Deregister(smeg::Entity& entity);

	void Process(smeg::Entity &entity);
	void Render(smeg::Entity &entity);
};