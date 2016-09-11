#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

#include "text_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/transform.hpp"
#include "../components/text.hpp"
#include "../../service/texture_library.hpp"

TextRenderer::TextRenderer() {
	types.push_back(std::type_index(typeid(Transform)));
	types.push_back(std::type_index(typeid(Text)));
}

void TextRenderer::Process(Entity &entity) {}

void TextRenderer::Render(BatchRenderer &renderer, Entity &entity) {
	Transform& transform = entity.GetComponent<Transform>();
	Text& text = entity.GetComponent<Text>();
	auto &textureLibrary = serviceContainer->Get<TextureLibrary>();

	if (text.fontTextureId.empty()) {

		SDL_Color textColor = SDL_Color { 0x0, 0x0, 0x0, 0xFF };
		SDL_Surface* textSurface = TTF_RenderText_Solid(text.font, text.text.c_str(), textColor);

		std::string key = textureLibrary.resPrefix + text.text;
		textureLibrary.Cache(key, textSurface); // TODO: Use a unique identifier
		text.fontTextureId = key;

		text.w = textSurface->w;
		text.h = textSurface->h;
		SDL_FreeSurface(textSurface);
	}

	SDL_Rect renderQuad = { (int)transform.position.x, (int)transform.position.y, text.w, text.h};
	renderer.Batch(textureLibrary.Get(text.fontTextureId), {}, renderQuad, text.layer);
}