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
#include <iostream>

using namespace smeg;

int main() {
	App app;
	app.Init();

	auto& mainScreen = app.CreateScreen();

	// Systems
	std::unique_ptr<System> drawSystem = std::make_unique<SpriteRenderer>();
	mainScreen.AddSystem(drawSystem);

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
			std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		} else {
			std::cout << "Font found!" << std::endl;
		}

		std::unique_ptr<Component> transform = std::make_unique<Transform>(20, 10);
		std::unique_ptr<Component> text = std::make_unique<Text>(std::string(""), font, 300, SDL_Color { 0x0, 0x77, 0x0, 0xFF });
		std::unique_ptr<Component> fps = std::make_unique<Fps>();

		entity->AddComponent(transform);
		entity->AddComponent(text);
		entity->AddComponent(fps);
		mainScreen.AddEntity(entity);
	}

	// Ducks
	for (int i = -100; i < 100; ++i) {
		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
		std::unique_ptr<Component> transform = std::make_unique<Transform>(i * 16 + i, (i * 16) + i);
		std::unique_ptr<Component> sprite = std::make_unique<Sprite>(std::string("res/duck.png"), 128, 128, 100 - i);

		entity->AddComponent(transform);
		entity->AddComponent(sprite);
		mainScreen.AddEntity(entity);
	}

	app.Start();
}