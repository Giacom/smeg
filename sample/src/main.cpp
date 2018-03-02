#include "app.hpp"
#include "ecs/systems/renderers/sprite_renderer.hpp"
#include "ecs/systems/renderers/text_renderer.hpp"
#include "ecs/systems/debug/fps_display.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/sprite.hpp"
#include "ecs/components/text.hpp"
#include "ecs/components/debug/fps.hpp"
#include "math/vector2.hpp"
#include "math/rect.hpp"

#include "test_component.hpp"
#include "test_system.hpp"

#include <memory>
#include <algorithm>

using namespace smeg;

i32 main(i32, char**) {
	App app;
	app.Init("SMEG Sample", 800, 600);

	auto& mainScreen = app.CreateScreen();

	// Systems
	std::unique_ptr<System> drawSystem = std::make_unique<SpriteRenderer>("res/sprite_shader.vert", "res/sprite_shader.frag");
	mainScreen.AddSystem(drawSystem);

	std::unique_ptr<System> fontSystem = std::make_unique<TextRenderer>("res/sprite_shader.vert", "res/text_shader.frag");
	mainScreen.AddSystem(fontSystem);

	std::unique_ptr<System> testSystem = std::make_unique<TestSystem>();
	mainScreen.AddSystem(testSystem);

	std::unique_ptr<System> fpsSystem = std::make_unique<FpsDisplay>();
	mainScreen.AddSystem(fpsSystem);


	/*
	std::unique_ptr<System> fpsDisplay = std::make_unique<FpsDisplay>();
	mainScreen.AddSystem(fpsDisplay);
	*/

	// Components
	// FPS Display
	/*
	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();


		std::unique_ptr<Component> transform = std::make_unique<Transform>(20, 10, 0, 0);
	//	std::unique_ptr<Component> text = std::make_unique<Text>(std::string(""), font, 300, SDL_Color { 0x0, 0x77, 0x0, 0xFF });
//		std::unique_ptr<Component> fps = std::make_unique<Fps>();

		entity->AddComponent(transform);
		// entity->AddComponent(text);
		// entity->AddComponent(fps);
		mainScreen.AddEntity(entity);
	}
	*/
	

	// Ducks
	
	/*
	for (i32 i = 8; i >= 0; i--) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(i * 100 + i, (i * 16) + i, i, 0);
		std::unique_ptr<Component> sprite = std::make_unique<Sprite>(i % 4 == 0 ? "res/duck.png" : "res/duck_opaque.jpg", Rect(), Vector2(200, 200));
		std::unique_ptr<Component> testComponent = std::make_unique<TestComponent>();

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		entity->AddComponent(testComponent);
		mainScreen.AddEntity(entity);
	}
	*/

	for (i32 i = 32; i >= 0; i--) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(i * 30 + i, 0, i, 0);

		std::unique_ptr<Component> sprite = std::make_unique<Sprite>("res/duck.png", Rect::New(), Vector2::New(128, 128));
		std::unique_ptr<Component> testComponent = std::make_unique<TestComponent>(i, i % 3);

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		entity->AddComponent(testComponent);
		mainScreen.AddEntity(entity);
	}

	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(-200, 0, 1000, 0);
		std::unique_ptr<Component> text = std::make_unique<Text>("SMEG DOES TEXT\nAND NEW LINES!", Vector2::New(2, 2));

		entity->AddComponent(transform);
		entity->AddComponent(text);

		mainScreen.AddEntity(entity);
	}

	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(-400, -290, 500, 0);
		std::unique_ptr<Component> text = std::make_unique<Text>("-100", Vector2::New(2, 2));
		std::unique_ptr<Component> fps = std::make_unique<Fps>();

		entity->AddComponent(transform);
		entity->AddComponent(text);
		entity->AddComponent(fps);

		mainScreen.AddEntity(entity);
	}

	app.Start();
	return 0;
}
