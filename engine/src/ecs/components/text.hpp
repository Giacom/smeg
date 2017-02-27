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
			std::vector<unsigned short> indices;

			unsigned int vbo = 0;
			unsigned int vao = 0;
			unsigned int ebo = 0;

			bool dirty = false;

		private:
			std::string text;
			// Colour colour;

		public:
			Text(std::string text, Vector2 size) : size(size), text(text) {}

			void SetText(std::string text) {
				// If are the same, just return.
				if (this->text.compare(text) == 0) {
					return;
				}
				this->dirty = true;
				this->text = text;
			}

			const std::string& GetText() const {
				return text;
			}
	};
}