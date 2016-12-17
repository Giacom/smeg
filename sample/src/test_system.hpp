#pragma once

#include "ecs/system.hpp"

struct TestSystem : public smeg::System {
	TestSystem();

	void Initialise(smeg::OpenGLRenderer& renderer);
	void Process(smeg::Entity &entity);
	void Render(smeg::OpenGLRenderer& renderer, smeg::SpriteBatchRenderer& batcher, smeg::Entity &entity);
};