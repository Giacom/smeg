#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "screen.hpp"

struct App {
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::vector<std::unique_ptr<Screen>> screens;

	~App();
	void Init();
	void Start();
	void Update();
	void Render();
};