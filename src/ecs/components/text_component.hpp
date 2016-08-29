#pragma once

#include <SDL/SDL_ttf.h>
#include <string>
#include "../component.hpp"
#include "../component_type.hpp"

struct TextComponent: public Component {

	static ComponentType type;

	int x;
	int y;

	std::string text;
	TTF_Font* font;

	~TextComponent() {}
	TextComponent(int x, int y, std::string text, TTF_Font* font) : Component(), x(x), y(y), text(text), font(font) {}
};