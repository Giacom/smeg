#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

#include "sprite_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/sprite.hpp"

SpriteRenderer::SpriteRenderer() {
	type = std::type_index(typeid(Sprite));
}

void SpriteRenderer::Process(Entity &entity) {

}

void SpriteRenderer::Render(SDL_Renderer *renderer, Entity &entity) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);

	Sprite *sprite = entity.GetComponent<Sprite>();
	const SDL_Rect rect = SDL_Rect { sprite->x, sprite->y, sprite->w, sprite->h };
	SDL_RenderFillRect(renderer, &rect);
}