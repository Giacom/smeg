#include "test_system.hpp"
#include "test_component.hpp"

#include "service/time.hpp"
#include "ecs/components/transform.hpp"

TestSystem::TestSystem() {
	types.push_back(std::type_index(typeid(TestComponent)));
	types.push_back(std::type_index(typeid(smeg::Transform)));
}

void TestSystem::Initialise(smeg::OpenGLRenderer&) {
}

void TestSystem::Process(smeg::Entity &entity) {
	smeg::Time &time = serviceContainer->Get<smeg::Time>();
	smeg::Transform &transform = entity.GetComponent<smeg::Transform>();

	transform.position.x += time.delta * 100;
};

void TestSystem::Render(smeg::OpenGLRenderer&, smeg::SpriteBatchRenderer&, smeg::Entity&) {
}