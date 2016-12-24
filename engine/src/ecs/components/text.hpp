#pragma once

#include <string>

#include "SDL.h"
// #include "graphics/colour.hpp"
// #include "graphics/font.hpp"
#include "ecs/component.hpp"

namespace smeg {
	struct Text: public Component {
		
		public:
			// Points to a texture
			std::string bitmapTextureId;
			std::string fontPath;

		private:
			std::string text;
			// Colour colour;

		public:
			//Text(std::string text, std::string fontPath, Colour colour) : fontPath(fontPath), text(text), colour(colour) {}

			void SetText(std::string text) {
				// If are the same, just return.
				if (this->text.compare(text) == 0) {
					return;
				}
				this->text = text;
			}

			const std::string& GetText() {
				return text;
			}
	};
}