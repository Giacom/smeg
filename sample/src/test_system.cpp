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

	transform.position.x += time.delta * 100.0f;

	transform.position.x = (fmod(transform.position.x * 2, 1024) - transform.position.x); 
	transform.position.y = (sin(transform.position.x * 0.01f + (float)(time.ticks) * 0.01f) * 50);
	transform.position.z = transform.position.x;

	if (time.ticks % 100 == 0) {
		//sprite.SetDrawRect(smeg::Rect::New(time.ticks / 100, time.ticks / 100, 32, 32)); 
		sprite.SetTexturePath("res/duck_opaque.jpg");
		sprite.SetDrawRect(smeg::Rect::New());
		sprite.size = smeg::Vector2::New(256, 256);
	}
};

void TestSystem::Render(smeg::OpenGLRenderer&, smeg::SpriteBatchRenderer&, smeg::Entity&) {
}