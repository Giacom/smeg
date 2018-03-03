#pragma once

#include "screen.hpp"

class TestScreen : public smeg::Screen {

	smeg::Texture duckTexture;

	void Initialise();
	void Update();
	void Render();
};