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

int main(int, char**) {
	App app;
	app.Init("SMEG Sample", 800, 600);

	auto& mainScreen = app.CreateScreen();

	// Systems
	std::unique_ptr<System> drawSystem = std::make_unique<SpriteRenderer>("res/sprite_shader.vert", "res/sprite_shader.frag");
	mainScreen.AddSystem(drawSystem);

	std::unique_ptr<System> fontSystem = std::make_unique<TextRenderer>("res/sprite_shader.vert", "res/sprite_shader.frag");
	mainScreen.AddSystem(fontSystem);

	std::unique_ptr<System> testSystem = std::make_unique<TestSystem>();
	mainScreen.AddSystem(testSystem);

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
	for (int i = 8; i >= 0; i--) {
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

/*
	for (int i = 32; i >= 0; i--) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(i * 30 + i, 0, i, 0);

		Rect drawRect = i % 2 == 0 ? Rect::New(0, 0, 32, 32) : Rect::New(32, 0, 32, 32);

		std::unique_ptr<Component> sprite = std::make_unique<Sprite>("res/duck_spritesheet.png", drawRect, Vector2::New(128, 128));
		std::unique_ptr<Component> testComponent = std::make_unique<TestComponent>();

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		entity->AddComponent(testComponent);
		mainScreen.AddEntity(entity);
	}
*/

	std::unique_ptr<Entity> entity = std::make_unique<Entity>();
	std::unique_ptr<Component> transform = std::make_unique<Transform>(-300, -300, 0, 0);
	std::unique_ptr<Component> text = std::make_unique<Text>("HELLO WORLD", Vector2::New(600, 400));

	entity->AddComponent(transform);
	entity->AddComponent(text);

	mainScreen.AddEntity(entity);

	app.Start();
	return 0;
}