#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include <memory>

#include "text_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/text_component.hpp"

void TextRenderer::Process(Entity &entity) {}

void TextRenderer::Render(SDL_Renderer *renderer, Entity &entity) {
	TextComponent *textComponent = entity.GetComponent<TextComponent>();
	SDL_Color textColor = SDL_Color { 0x0, 0x0, 0x0, 0xFF };
	SDL_Surface* textSurface = TTF_RenderText_Solid(textComponent->font, textComponent->text.c_str(), textColor);

	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
	int textWidth = textSurface->w;
	int textHeight = textSurface->h;

	SDL_Rect renderQuad = { textComponent->x, textComponent->y, textWidth, textHeight };
	SDL_RenderCopy(renderer, text, NULL, &renderQuad);
	SDL_DestroyTexture(text);
}