#pragma once

#include <string>
#include <vector>

#include "SDL.h"
// #include "graphics/colour.hpp"
// #include "graphics/font.hpp"
#include "ecs/component.hpp"
#include "math/vector2.hpp"

namespace smeg {
	struct Text: public Component {
		
		public:
			// Points to a texture
			std::string bitmapTextureId;
			std::string fontPath;
			Vector2 size;

			std::vector<float> vertices;

			const std::vector<unsigned short> indices = {
				0, 1, 2,
				2, 3, 0,
			};

			unsigned int vbo;
			unsigned int vao;
			unsigned int ebo;

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