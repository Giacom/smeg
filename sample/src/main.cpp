#include "app.hpp"
#include "ecs/systems/renderers/sprite_renderer.hpp"
#include "ecs/systems/renderers/text_renderer.hpp"
#include "ecs/systems/debug/fps_display.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/sprite.hpp"
#include "ecs/components/text.hpp"
#include "ecs/components/debug/fps.hpp"

#include <memory>
#include <algorithm>

using namespace smeg;

int main(int, char**) {
	App app;
	app.Init(800, 600);
	auto& mainScreen = app.CreateScreen();

	// Systems
	std::unique_ptr<System> drawSystem = std::make_unique<SpriteRenderer>();
	mainScreen.AddSystem(drawSystem);

	/*
	std::unique_ptr<System> textDrawSystem = std::make_unique<TextRenderer>();
	mainScreen.AddSystem(textDrawSystem);

	std::unique_ptr<System> fpsDisplay = std::make_unique<FpsDisplay>();
	mainScreen.AddSystem(fpsDisplay);

	// Components
	// FPS Display
	{
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();

		TTF_Font *font = TTF_OpenFont("res/arial.ttf", 24);
		if (!font) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading font: %s", TTF_GetError());
		} else {
			SDL_Log("Font found!");
		}

		std::unique_ptr<Component> transform = std::make_unique<Transform>(20, 10);
		std::unique_ptr<Component> text = std::make_unique<Text>(std::string(""), font, 300, SDL_Color { 0x0, 0x77, 0x0, 0xFF });
		std::unique_ptr<Component> fps = std::make_unique<Fps>();

		entity->AddComponent(transform);
		entity->AddComponent(text);
		entity->AddComponent(fps);
		mainScreen.AddEntity(entity);
	}
	*/

	// Ducks
	for (int i = -10; i < 10; ++i) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(i * 16 + i, (i * 16) + i, 0, 0);
		std::unique_ptr<Component> sprite = std::make_unique<Sprite>("res/duck.png", 128, 128, 100 - i);

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		mainScreen.AddEntity(entity);
	}

	app.Start();
	return 0;
}