#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

#include "text_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/transform.hpp"
#include "../components/text.hpp"
#include "../../service/texture_library.hpp"
#include "../../service/time.hpp"


TextRenderer::TextRenderer() {
	types.push_back(std::type_index(typeid(Transform)));
	types.push_back(std::type_index(typeid(Text)));
}

void TextRenderer::Process(Entity &entity) {
	Text &text = entity.GetComponent<Text>();
	Time &time = serviceContainer->Get<Time>();

	unsigned long blah = time.current % 1000;
	if (blah == 0) {
		text.SetText(std::to_string(time.current));
	} 
}

void TextRenderer::Render(BatchRenderer &renderer, Entity &entity) {
	Transform &transform = entity.GetComponent<Transform>();
	Text &text = entity.GetComponent<Text>();
	auto &textureLibrary = serviceContainer->Get<TextureLibrary>();

	if (text.textChanged) {

		// Remove old cached version
		if (!text.fontTextureId.empty()) {
			textureLibrary.Remove(text.fontTextureId);
		}

		SDL_Color textColor = SDL_Color { 0x0, 0x0, 0x0, 0xFF };
		SDL_Surface* textSurface = TTF_RenderText_Solid(text.font, text.GetText().c_str(), textColor);
		
		std::string key = textureLibrary.resPrefix + text.GetText();

		textureLibrary.Cache(key, textSurface); // TODO: Use a unique identifier
		text.fontTextureId = key;

		text.w = textSurface->w;
		text.h = textSurface->h;

		text.textChanged = false;

		SDL_FreeSurface(textSurface);
	}

	SDL_Rect renderQuad = { (int)transform.position.x, (int)transform.position.y, text.w, text.h};
	renderer.Batch(textureLibrary.Get(text.fontTextureId), {}, renderQuad, text.layer);
}