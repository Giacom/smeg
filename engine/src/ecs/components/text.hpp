#pragma once

#include <string>

#include "SDL.h"
#include "ecs/component.hpp"

namespace smeg {
	struct Text: public Component {
		
		public:
			// Points to a texture
			std::string fontTextureId;

		private:
			std::string text;

		public:

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