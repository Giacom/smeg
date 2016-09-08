#pragma once

#include <SDL/SDL_ttf.h>
#include <string>
#include "../component.hpp"

struct Text: public Component {
	
	std::string text;
	TTF_Font* font;

	~Text() {}
	Text(std::string text, TTF_Font* font) : Component(), text(text), font(font) {}
};