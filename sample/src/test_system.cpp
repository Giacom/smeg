#include <cmath>

#include "test_system.hpp"
#include "test_component.hpp"

#include "service/time.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/sprite.hpp"

#include "SDL.h"

TestSystem::TestSystem() {
	types.push_back(std::type_index(typeid(TestComponent)));
	types.push_back(std::type_index(typeid(smeg::Transform)));
	types.push_back(std::type_index(typeid(smeg::Sprite)));
}

void TestSystem::Initialise(smeg::OpenGLRenderer&) {
	SDL_Log("Test system initialised");
}

void TestSystem::Register(smeg::OpenGLRenderer&, smeg::Entity& entity) {
	SDL_Log("Test system registered for entity %p.", (void*) &entity);
}

void TestSystem::Deregister(smeg::OpenGLRenderer&, smeg::Entity& entity) {
	SDL_Log("Test system deregistered for entity %p.", (void*) &entity);
}

void TestSystem::Process(smeg::Entity &entity) {
	smeg::Time &time = serviceContainer->Get<smeg::Time>();
	smeg::Transform &transform = entity.GetComponent<smeg::Transform>();
	smeg::Sprite &sprite = entity.GetComponent<smeg::Sprite>();
	TestComponent& testComponent = entity.GetComponent<TestComponent>();

	transform.position.x += time.delta * 100.0f;

	transform.position.x = (fmod(transform.position.x * 2, 1024) - transform.position.x); 
	transform.position.y = (sin(transform.position.x * 0.01f + (float)(time.ticks) * 0.01f) * 50);
	transform.position.z = transform.position.x;

	float size = (4.0f + sin((float)time.ticks * 0.01f)) * 16.0f;

	if (time.ticks % 100 == 0) {	
		testComponent.duckShown = (testComponent.duckShown + 1) % 3;

		switch (testComponent.duckShown) {
			case 2:
				sprite.SetTexturePath("res/duck.png");
				sprite.SetDrawRect(smeg::Rect::New());
				break;

			case 1:
				sprite.SetTexturePath("res/duck_opaque.jpg");
				sprite.SetDrawRect(smeg::Rect::New());
				break;

			case 0:
				sprite.SetTexturePath("res/duck_spritesheet.png");
				smeg::Rect drawRect = testComponent.duckIndex % 2 == 0 ? smeg::Rect::New(0, 0, 32, 32) : smeg::Rect::New(32, 0, 32, 32);
				sprite.SetDrawRect(drawRect);
				break;
		}
	}

	sprite.size = smeg::Vector2::New(size, size);
};

void TestSystem::Render(smeg::OpenGLRenderer&, smeg::SpriteBatchRenderer&, smeg::Entity&) {
}