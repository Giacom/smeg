#include "test_screen.hpp"
#include "io/image.hpp"

void TestScreen::Initialise() {
	duckTexture = graphics->LoadTexture(smeg::Image::LoadFromFile("res/duck_spritesheet.png"));
}

void TestScreen::Update() {
}

void TestScreen::Render() {
	graphics->DrawTexture(duckTexture, smeg::Vector2::New(0, 0));
}
