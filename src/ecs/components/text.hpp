#pragma once

#include <SDL/SDL_ttf.h>
#include <string>
#include "../component.hpp"
#include "../../res/texture.hpp"

struct Text: public Component {
	
	std::string text;
	TTF_Font* font;
	std::string fontTextureId;

	int w, h;
	int layer;

	~Text() {}
	Text(std::string text, TTF_Font* font, int layer = 0) : Component(), text(text), font(font), layer(layer) {}
};