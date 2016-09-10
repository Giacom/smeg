#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "screen.hpp"
#include "service/service_container.hpp"

struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::vector<std::unique_ptr<Screen>> screens;
	ServiceContainer serviceContainer;

	~App();
	void Init();
	void Start();
	bool ProcessEvents();
	void Update();
	void Render();
};