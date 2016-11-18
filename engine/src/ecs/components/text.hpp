#pragma once

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "../component.hpp"

namespace smeg {
	struct Text: public Component {
		
		public:
			TTF_Font* font;

			std::string fontTextureId;
			bool isDirty;

			int w, h;
			int layer;

		private:
			std::string text;
			SDL_Color colour;

		public:
			~Text() {}
			Text(std::string text, TTF_Font* font, int layer = 0, SDL_Color colour = { 0x0, 0x0, 0x0, 0xFF}) :
				Component(), font(font), isDirty(true), layer(layer), text(text), colour(colour) {}

			void SetText(std::string text) {
				// If are the same, just return.
				if (this->text.compare(text) == 0) {
					return;
				}
				this->text = text;
				isDirty = true;
			}

			const std::string& GetText() {
				return text;
			}

			void SetColour(struct SDL_Color colour) {
				if (this->colour.a == colour.a && this->colour.g == colour.g &&
					this->colour.b == colour.b && this->colour.a == colour.a) {
					return;
				}
				this->colour = colour;
				isDirty = true;
			}

			const SDL_Color& GetColour() {
				return colour;
			}
	};
}