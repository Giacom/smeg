#pragma once

#include "ecs/system.hpp"

struct TestSystem : public smeg::System {
	TestSystem();

	void Initialise(smeg::OpenGLRenderer& renderer);

	void Register(smeg::OpenGLRenderer& renderer, smeg::Entity& entity);
	void Deregister(smeg::OpenGLRenderer& renderer, smeg::Entity& entity);

	void Process(smeg::Entity &entity);
	void Render(smeg::OpenGLRenderer& renderer, smeg::SpriteBatchRenderer& batcher, smeg::Entity &entity);
};