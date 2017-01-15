#pragma once

#include <string>
#include "ecs/component.hpp"
#include "math/rect.hpp"
#include "math/vector2.hpp"

namespace smeg {

	class Sprite: public Component {

		private:
			std::string texturePath;
			Rect drawRect;
			bool isDirty = true;

		public:
			unsigned int vbo = 0;
			unsigned int vao = 0;
			unsigned int ebo = 0;

			Vector2 size;
			
			std::vector<float> vertices;

			const std::vector<unsigned short> indices = {
				0, 1, 2,
				2, 3, 0,
			};

			Sprite(const std::string texturePath, Rect drawRect, Vector2 size) :
				Component(), texturePath(texturePath), drawRect(drawRect), size(size) {}

			void SetTexturePath(std::string texturePath) {
				this->texturePath = texturePath;
				isDirty = true;
			}

			const std::string& GetTexturePath() {
				return this->texturePath;
			}

			void SetDrawRect(Rect drawRect) {
				this->drawRect = drawRect;
				isDirty = true;
			}

			Rect GetDrawRect() {
				return this->drawRect;
			}

			bool IsDirty() {
				return this->isDirty;
			}
	};
}