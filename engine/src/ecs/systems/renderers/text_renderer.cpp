#include "SDL.h"
#include <memory>

#include "text_renderer.hpp"
#include "ecs/system.hpp"
#include "ecs/entity.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/text.hpp"
#include "service/texture_library.hpp"
#include "service/time.hpp"

namespace smeg {

	TextRenderer::TextRenderer() {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Text)));
		executionOrder = System::LATE;
	}

	void TextRenderer::Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity) {
        /*
		Transform &transform = entity.GetComponent<Transform>();
		Text &text = entity.GetComponent<Text>();

		if (text.GetText().size() <= 0) {
			return;
		}

		auto &textureLibrary = serviceContainer->Get<TextureLibrary>();

		if (text.isDirty) {

			// Remove old cached version
			if (!text.fontTextureId.empty()) {
				textureLibrary.Remove(text.fontTextureId);
			}

			SDL_Surface* textSurface = TTF_RenderText_Solid(text.font, text.GetText().c_str(), text.GetColour());
			
			std::string key = textureLibrary.resPrefix + "text::" + std::to_string(text.id);

			textureLibrary.Cache(key, textSurface); // TODO: Use a unique identifier
			text.fontTextureId = key;

			text.w = textSurface->w;
			text.h = textSurface->h;

			text.isDirty = false;

			SDL_FreeSurface(textSurface);
		}

		SDL_Rect renderQuad = { (int)transform.position.x, (int)transform.position.y, text.w, text.h};
		renderer.BatchTexture(textureLibrary.Get(text.fontTextureId), {}, renderQuad, text.layer);
        */
	}
}