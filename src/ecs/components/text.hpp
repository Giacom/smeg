#pragma once

#include <SDL/SDL_ttf.h>
#include <string>
#include "../component.hpp"
#include "../../res/texture.hpp"

struct Text: public Component {
	
	public:
		TTF_Font* font;

		std::string fontTextureId;
		bool textChanged;

		int w, h;
		int layer;

	private:
		std::string text;

	public:
		~Text() {}
		Text(std::string text, TTF_Font* font, int layer = 0) : Component(), font(font), textChanged(true), layer(layer), text(text) {}

		void SetText(std::string text) {
			// If are the same, just return.
			if (this->text.compare(text) == 0) {
				return;
			}
			this->text = text;
			textChanged = true;
		}

		const std::string& GetText() {
			return text;
		}
};