#pragma once

#include "ecs/system.hpp"

namespace smeg {

	struct FpsDisplay: public System {
		FpsDisplay();
		void Initialise();
		void Register(Entity &entity);
		void Deregister(Entity &entity);
		void Process(Entity &entity);
		void Render(Entity &entity);
	};
}