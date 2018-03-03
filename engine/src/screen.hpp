#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "graphics/graphics.hpp"
#include "service/service_container.hpp"

namespace smeg {
	class Screen {
		public:
			bool active = true;
			Graphics* graphics;
			ServiceContainer* serviceContainer;

			virtual void Initialise() = 0;
			virtual void Update() = 0;
			virtual void Render() = 0;
	};
}