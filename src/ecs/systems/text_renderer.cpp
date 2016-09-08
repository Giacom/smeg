#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

#include "text_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/transform.hpp"
#include "../components/text.hpp"

TextRenderer::TextRenderer() {
	types.push_back(std::type_index(typeid(Transform)));
	types.push_back(std::type_index(typeid(Text)));
}

void TextRenderer::Process(Entity &entity) {}

void TextRenderer::Render(SDL_Renderer *renderer, Entity &entity) {
	Transform *transform = entity.GetComponent<Transform>();
	Text *text = entity.GetComponent<Text>();

	SDL_Color textColor = SDL_Color { 0x0, 0x0, 0x0, 0xFF };
	SDL_Surface* textSurface = TTF_RenderText_Solid(text->font, text->text.c_str(), textColor);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	int textWidth = textSurface->w;
	int textHeight = textSurface->h;

	SDL_Rect renderQuad = { (int)transform->position.x, (int)transform->position.y, textWidth, textHeight };
	SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
	SDL_DestroyTexture(texture);
}